param(
    [string]$XmlPath = "C:\GitUnity\Winapi-btd-5\Resource\InGame.xml",
    [string]$OutPath = "C:\Users\inha\AppData\Local\Temp\claude\C--GitUnity-Winapi-btd-5\ed3b9fac-182b-4812-879b-10890ff5d812\scratchpad\InGame_SpriteList.md"
)

[xml]$xml = Get-Content -Path $XmlPath -Raw
$frameInfo = $xml.SpriteInformation.FrameInformation
$texW = $frameInfo.texw
$texH = $frameInfo.texh
$texType = $frameInfo.type

$animNodes = $frameInfo.ChildNodes | Where-Object { $_.LocalName -eq 'Animation' }
$cellNodes = $frameInfo.ChildNodes | Where-Object { $_.LocalName -eq 'Cell' }

# entry: Name, Category, Kind(anim/single), FrameNames(list), SizeText
$entries = @()

foreach ($a in $animNodes) {
    $cells = @($a.Cell)
    $sizes = @($cells | ForEach-Object { "$($_.aw)x$($_.ah)" } | Select-Object -Unique)
    $sizeText = if ($sizes.Count -eq 1) { $sizes[0] } else { "가변(" + ($sizes -join ", ") + ")" }
    $entries += [PSCustomObject]@{
        Name     = $a.name
        Category = ($a.name -split '_')[0]
        Kind     = "애니메이션"
        Count    = $cells.Count
        Detail   = ($cells | ForEach-Object { $_.name }) -join ", "
        Size     = $sizeText
    }
}

# group standalone cells that look like numbered sequences: base_NN
$cellList = $cellNodes | ForEach-Object {
    [PSCustomObject]@{ Name = $_.name; W = $_.aw; H = $_.ah }
}

$used = New-Object 'System.Collections.Generic.HashSet[string]'
$byBase = @{}
foreach ($c in $cellList) {
    if ($c.Name -match '^(.+)_(\d{2})$') {
        $base = $Matches[1]
        if (-not $byBase.ContainsKey($base)) { $byBase[$base] = @() }
        $byBase[$base] += $c
    }
}

foreach ($base in $byBase.Keys) {
    $group = $byBase[$base] | Sort-Object Name
    if ($group.Count -ge 2) {
        foreach ($g in $group) { [void]$used.Add($g.Name) }
        $sizes = @($group | ForEach-Object { "$($_.W)x$($_.H)" } | Select-Object -Unique)
        $sizeText = if ($sizes.Count -eq 1) { $sizes[0] } else { "가변(" + ($sizes -join ", ") + ")" }
        $first = $group[0].Name
        $last = $group[-1].Name
        $entries += [PSCustomObject]@{
            Name     = $base
            Category = ($base -split '_')[0]
            Kind     = "연속셀"
            Count    = $group.Count
            Detail   = "$first ~ $last"
            Size     = $sizeText
        }
    }
}

foreach ($c in $cellList) {
    if (-not $used.Contains($c.Name)) {
        $entries += [PSCustomObject]@{
            Name     = $c.Name
            Category = ($c.Name -split '_')[0]
            Kind     = "단일"
            Count    = 1
            Detail   = ""
            Size     = "$($c.W)x$($c.H)"
        }
    }
}

$categories = $entries | Group-Object Category | Sort-Object Name

$sb = New-Object System.Text.StringBuilder
[void]$sb.AppendLine("# InGame.xml 스프라이트 아틀라스 정리")
[void]$sb.AppendLine()
[void]$sb.AppendLine("원본: ``Resource/InGame.xml``")
[void]$sb.AppendLine()
[void]$sb.AppendLine("- 텍스처 크기: ${texW} x ${texH} (${texType})")
[void]$sb.AppendLine("- 애니메이션 그룹: $($animNodes.Count)개")
[void]$sb.AppendLine("- 연속 번호 셀 그룹(자동 인식): $(($entries | Where-Object {$_.Kind -eq '연속셀'}).Count)개")
[void]$sb.AppendLine("- 단일 셀: $(($entries | Where-Object {$_.Kind -eq '단일'}).Count)개")
[void]$sb.AppendLine("- 항목(카테고리) 수: $($categories.Count)개")
[void]$sb.AppendLine()
[void]$sb.AppendLine("표 형식: **이름 | 종류 | 개수 | 크기(px) | 세부**")
[void]$sb.AppendLine("- 종류: 애니메이션(``<Animation>`` 태그로 묶인 프레임) / 연속셀(번호가 이어지는 개별 ``<Cell>``, 자동 추정) / 단일(개별 이미지 하나)")
[void]$sb.AppendLine("- 크기: 셀의 논리적 전체 크기(aw x ah) 기준. 프레임마다 다르면 '가변'으로 표시")
[void]$sb.AppendLine()
[void]$sb.AppendLine("## 목차")
[void]$sb.AppendLine()
$toc = $categories | ForEach-Object {
    $anchor = ($_.Name -replace '[^a-zA-Z0-9가-힣]', '').ToLower()
    "[$($_.Name)](#$anchor) ($($_.Count))"
}
[void]$sb.AppendLine(($toc -join " · "))
[void]$sb.AppendLine()

foreach ($cat in $categories) {
    [void]$sb.AppendLine("## $($cat.Name)")
    [void]$sb.AppendLine()
    [void]$sb.AppendLine("| 이름 | 종류 | 개수 | 크기 | 세부 |")
    [void]$sb.AppendLine("|---|---|---|---|---|")
    $sortedItems = $cat.Group | Sort-Object Name
    foreach ($e in $sortedItems) {
        $detail = $e.Detail
        if ($detail.Length -gt 80) { $detail = $detail.Substring(0, 77) + "..." }
        [void]$sb.AppendLine("| $($e.Name) | $($e.Kind) | $($e.Count) | $($e.Size) | $detail |")
    }
    [void]$sb.AppendLine()
}

[System.IO.File]::WriteAllText($OutPath, $sb.ToString(), (New-Object System.Text.UTF8Encoding($true)))
"Done. Categories: $($categories.Count), Total entries: $($entries.Count)"
"Output: $OutPath"
