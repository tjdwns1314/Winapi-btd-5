# InGame.xml 스프라이트 아틀라스 정리

원본: `Resource/InGame.xml`

- 텍스처 크기: 3984 x 3964 (jpng)
- 애니메이션 그룹: 119개
- 연속 번호 셀 그룹(자동 인식): 56개
- 단일 셀: 782개
- 항목(카테고리) 수: 114개

표 형식: **이름 | 종류 | 개수 | 크기(px) | 세부**
- 종류: 애니메이션(`<Animation>` 태그로 묶인 프레임) / 연속셀(번호가 이어지는 개별 `<Cell>`, 자동 추정) / 단일(개별 이미지 하나)
- 크기: 셀의 논리적 전체 크기(aw x ah) 기준. 프레임마다 다르면 '가변'으로 표시

## 목차

[absolute](#absolute) (1) · [acorn](#acorn) (1) · [agent](#agent) (1) · [angry](#angry) (7) · [apprentice](#apprentice) (2) · [banana](#banana) (17) · [bananas](#bananas) (1) · [barrel1](#barrel1) (1) · [barrel2](#barrel2) (1) · [barrel3](#barrel3) (1) · [barrel4](#barrel4) (1) · [base](#base) (1) · [bee](#bee) (1) · [beekeeper](#beekeeper) (5) · [bfb](#bfb) (5) · [bin](#bin) (1) · [black](#black) (3) · [blade](#blade) (1) · [blimp](#blimp) (4) · [bloon](#bloon) (6) · [bloonberry](#bloonberry) (4) · [bloonchipper](#bloonchipper) (24) · [bloonsday](#bloonsday) (14) · [blue](#blue) (1) · [bomb](#bomb) (53) · [boomerang](#boomerang) (31) · [buccaneer](#buccaneer) (19) · [camo](#camo) (2) · [candy](#candy) (16) · [ceramic](#ceramic) (2) · [cobra](#cobra) (1) · [confused](#confused) (1) · [confusion](#confusion) (1) · [dart](#dart) (34) · [dartling](#dartling) (25) · [engineer](#engineer) (24) · [evil](#evil) (2) · [explosion](#explosion) (2) · [firework](#firework) (1) · [fireworks](#fireworks) (32) · [frag](#frag) (1) · [frosted](#frosted) (1) · [general](#general) (1) · [glaive](#glaive) (2) · [glue](#glue) (43) · [golden](#golden) (4) · [grape](#grape) (1) · [green](#green) (1) · [grilled](#grilled) (1) · [ground](#ground) (3) · [helicopter](#helicopter) (21) · [helipad](#helipad) (4) · [hot](#hot) (1) · [ice](#ice) (27) · [juggernaut](#juggernaut) (2) · [kick](#kick) (4) · [large](#large) (1) · [lead](#lead) (3) · [maelstrom](#maelstrom) (1) · [meerkat](#meerkat) (6) · [mm](#mm) (3) · [moab](#moab) (3) · [monkey](#monkey) (97) · [mortar](#mortar) (20) · [muzzle](#muzzle) (1) · [napalm](#napalm) (2) · [navy](#navy) (27) · [ninja](#ninja) (16) · [phoenix](#phoenix) (1) · [pineapple](#pineapple) (2) · [pirates](#pirates) (1) · [plaster](#plaster) (1) · [pontoon](#pontoon) (2) · [pop](#pop) (2) · [portable](#portable) (6) · [purple](#purple) (1) · [rad](#rad) (14) · [radoblaster](#radoblaster) (1) · [rainbow](#rainbow) (2) · [red](#red) (1) · [ring](#ring) (1) · [sentry](#sentry) (8) · [shockwave](#shockwave) (3) · [small](#small) (1) · [smoke](#smoke) (1) · [sniper](#sniper) (35) · [snowball](#snowball) (1) · [spectre](#spectre) (1) · [spike](#spike) (18) · [spiked](#spiked) (5) · [spikeopult](#spikeopult) (2) · [splodey](#splodey) (2) · [steampunk](#steampunk) (19) · [stock](#stock) (4) · [submarine](#submarine) (38) · [supermonkey](#supermonkey) (46) · [supply](#supply) (2) · [tack](#tack) (20) · [tacks](#tacks) (1) · [tech](#tech) (2) · [tempest](#tempest) (1) · [topgun](#topgun) (7) · [track](#track) (1) · [tribal](#tribal) (6) · [triple](#triple) (1) · [turret1](#turret1) (1) · [turret2](#turret2) (1) · [ufo](#ufo) (22) · [village](#village) (2) · [whirlwind](#whirlwind) (1) · [white](#white) (3) · [wizard](#wizard) (12) · [zebra](#zebra) (2) · [zomg](#zomg) (6)

## absolute

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| absolute_zero_wind_01 | 단일 | 1 | 205x99 |  |

## acorn

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| acorn | 단일 | 1 | 37x48 |  |

## agent

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| agent_box | 단일 | 1 | 148x148 |  |

## angry

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| angry_squirrel | 단일 | 1 | 49x126 |  |
| angry_squirrel_arm | 애니메이션 | 3 | 가변(16x44, 30x34, 35x19) | angry_squirrel_arm_01, angry_squirrel_arm_02, angry_squirrel_arm_03 |
| angry_squirrel_arm_green | 애니메이션 | 3 | 가변(29x62, 42x53, 56x29) | angry_squirrel_arm_green_01, angry_squirrel_arm_green_02, angry_squirrel_arm_... |
| angry_squirrel_arm_pro | 애니메이션 | 3 | 가변(37x86, 66x71, 75x44) | angry_squirrel_arm_pro_01, angry_squirrel_arm_pro_02, angry_squirrel_arm_pro_03 |
| angry_squirrel_green | 단일 | 1 | 60x160 |  |
| angry_squirrel_pro | 단일 | 1 | 146x196 |  |
| angry_squirrel_smoke | 애니메이션 | 4 | 가변(65x57, 129x104, 157x161, 164x179) | angry_squirrel_smoke_01, angry_squirrel_smoke_02, angry_squirrel_smoke_03, an... |

## apprentice

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| apprentice_seeking_core | 단일 | 1 | 73x73 |  |
| apprentice_seeking_flame | 연속셀 | 2 | 가변(71x90, 70x104) | apprentice_seeking_flame_01 ~ apprentice_seeking_flame_02 |

## banana

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| banana_box | 단일 | 1 | 98x116 |  |
| banana_farm_bank | 단일 | 1 | 93x141 |  |
| banana_farm_bank_text | 단일 | 1 | 83x20 |  |
| banana_farm_brick_base | 단일 | 1 | 94x188 |  |
| banana_farm_chimney | 애니메이션 | 2 | 76x97 | banana_farm_chimney_01, banana_farm_chimney_02 |
| banana_farm_earth_base | 단일 | 1 | 188x188 |  |
| banana_farm_enclosure | 단일 | 1 | 79x169 |  |
| banana_farm_investment | 단일 | 1 | 91x198 |  |
| banana_farm_investment_text | 단일 | 1 | 83x28 |  |
| banana_farm_more_bananas | 단일 | 1 | 91x90 |  |
| banana_farm_plantation | 단일 | 1 | 146x134 |  |
| banana_farm_republic | 단일 | 1 | 98x199 |  |
| banana_farm_research_facility | 단일 | 1 | 190x196 |  |
| banana_farm_smoke | 애니메이션 | 4 | 79x51 | banana_farm_smoke_01, banana_farm_smoke_02, banana_farm_smoke_03, banana_farm... |
| banana_farm_tree | 단일 | 1 | 115x135 |  |
| banana_farm_tree_bananas | 단일 | 1 | 86x72 |  |
| banana_farm_window | 애니메이션 | 3 | 132x9 | banana_farm_window_01, banana_farm_window_02, banana_farm_window_03 |

## bananas

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| bananas | 단일 | 1 | 99x76 |  |

## barrel1

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| barrel1 | 연속셀 | 4 | 128x192 | barrel1_01 ~ barrel1_04 |

## barrel2

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| barrel2 | 연속셀 | 4 | 128x192 | barrel2_01 ~ barrel2_04 |

## barrel3

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| barrel3 | 연속셀 | 4 | 128x192 | barrel3_01 ~ barrel3_04 |

## barrel4

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| barrel4 | 연속셀 | 4 | 128x192 | barrel4_01 ~ barrel4_04 |

## base

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| base | 연속셀 | 3 | 가변(128x192, 70x136) | base_01 ~ base_04 |

## bee

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| bee | 단일 | 1 | 102x71 |  |

## beekeeper

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| beekeeper_body | 단일 | 1 | 140x133 |  |
| beekeeper_hive | 단일 | 1 | 107x107 |  |
| beekeeper_lower_arm | 단일 | 1 | 49x55 |  |
| beekeeper_pro | 단일 | 1 | 151x153 |  |
| beekeeper_pro_bandana | 애니메이션 | 3 | 32x57 | beekeeper_pro_bandana_01, beekeeper_pro_bandana_02, beekeeper_pro_bandana_03 |

## bfb

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| bfb_eating | 연속셀 | 5 | 가변(526x355, 518x324, 498x317, 463x245, 239x220) | bfb_eating_01 ~ bfb_eating_05 |
| bfb_engine | 단일 | 1 | 147x158 |  |
| bfb_logo | 단일 | 1 | 218x218 |  |
| bfb_tail | 애니메이션 | 2 | 가변(140x143, 279x143) | bfb_tail_01, bfb_tail_02 |
| bfb_undamaged | 단일 | 1 | 152x609 |  |

## bin

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| bin | 단일 | 1 | 157x170 |  |

## black

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| black_bandana | 단일 | 1 | 82x28 |  |
| black_ninja_arm | 애니메이션 | 3 | 가변(63x61, 63x58) | black_ninja_arm_01, black_ninja_arm_02, black_ninja_arm_03 |
| black_smoke | 연속셀 | 4 | 가변(84x86, 152x158, 226x230, 230x248) | black_smoke_01 ~ black_smoke_04 |

## blade

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| blade_symbol_btd1 | 단일 | 1 | 52x52 |  |

## blimp

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| blimp_broken_rotor | 단일 | 1 | 149x54 |  |
| blimp_damage_01_1 | 단일 | 1 | 98x88 |  |
| blimp_damage_01_2 | 단일 | 1 | 88x90 |  |
| blimp_damage_02 | 단일 | 1 | 350x344 |  |

## bloon

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| bloon_scrambler_bell_a | 단일 | 1 | 225x307 |  |
| bloon_scrambler_bell_b | 단일 | 1 | 130x153 |  |
| bloon_scrambler_hub | 단일 | 1 | 135x133 |  |
| bloon_scrambler_ringer_a | 단일 | 1 | 148x99 |  |
| bloon_scrambler_ringer_b | 단일 | 1 | 133x206 |  |
| bloon_scrambler_sound_wave | 단일 | 1 | 90x321 |  |

## bloonberry

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| bloonberry | 애니메이션 | 10 | 가변(87x63, 91x65, 91x76, 111x93, 137x115, 137x133, 169x165, 169x184) | bloonberry_00, bloonberry_01, bloonberry_02, bloonberry_03, bloonberry_04, bl... |
| bloonberry_pro | 애니메이션 | 10 | 가변(87x63, 91x65, 91x76, 111x93, 137x115, 137x133, 169x165, 169x184) | bloonberry_pro_00, bloonberry_pro_01, bloonberry_pro_02, bloonberry_pro_03, b... |
| bloonberry_pro_tendril_holes | 단일 | 1 | 89x80 |  |
| bloonberry_tendril | 애니메이션 | 3 | 가변(64x67, 70x82, 73x92) | bloonberry_tendril_01, bloonberry_tendril_02, bloonberry_tendril_03 |

## bloonchipper

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| bloonchipper_base | 단일 | 1 | 76x75 |  |
| bloonchipper_blimp_fragments | 단일 | 1 | 12x14 |  |
| bloonchipper_exhaust_blue | 단일 | 1 | 41x45 |  |
| bloonchipper_exhaust_grey | 단일 | 1 | 41x45 |  |
| bloonchipper_expulsion_pipe | 단일 | 1 | 52x86 |  |
| bloonchipper_expulsion_vent | 단일 | 1 | 36x19 |  |
| bloonchipper_flame_overlay | 단일 | 1 | 38x30 |  |
| bloonchipper_funnel_drop_shadow | 단일 | 1 | 28x70 |  |
| bloonchipper_glow | 단일 | 1 | 150x150 |  |
| bloonchipper_hook | 단일 | 1 | 28x38 |  |
| bloonchipper_intake_pipe | 단일 | 1 | 37x97 |  |
| bloonchipper_intake_pipe_large | 단일 | 1 | 48x97 |  |
| bloonchipper_intake_vent | 단일 | 1 | 58x30 |  |
| bloonchipper_intake_vent_large | 단일 | 1 | 80x30 |  |
| bloonchipper_large_stripes | 단일 | 1 | 33x73 |  |
| bloonchipper_large_stripes_long | 단일 | 1 | 44x71 |  |
| bloonchipper_particle | 단일 | 1 | 33x32 |  |
| bloonchipper_small_wheel | 단일 | 1 | 44x27 |  |
| bloonchipper_thin_stripes | 단일 | 1 | 60x21 |  |
| bloonchipper_thin_stripes_long | 단일 | 1 | 78x21 |  |
| bloonchipper_vent_flare | 단일 | 1 | 66x114 |  |
| bloonchipper_wheel | 단일 | 1 | 26x51 |  |
| bloonchipper_wheel_arch | 단일 | 1 | 29x54 |  |
| bloonchipper_wind | 단일 | 1 | 50x62 |  |

## bloonsday

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| bloonsday_ball | 단일 | 1 | 70x70 |  |
| bloonsday_ball_pro | 단일 | 1 | 70x70 |  |
| bloonsday_ball_shadow | 단일 | 1 | 52x44 |  |
| bloonsday_laser_flare | 연속셀 | 4 | 109x196 | bloonsday_laser_flare_01 ~ bloonsday_laser_flare_04 |
| bloonsday_pro_ball_shields | 단일 | 1 | 132x144 |  |
| bloonsday_pro_plasma | 단일 | 1 | 123x126 |  |
| bloonsday_pro_pulsing_beam | 애니메이션 | 3 | 60x12 | bloonsday_pro_pulsing_beam_01, bloonsday_pro_pulsing_beam_02, bloonsday_pro_p... |
| bloonsday_pro_pulsing_core | 애니메이션 | 3 | 60x120 | bloonsday_pro_pulsing_core_01, bloonsday_pro_pulsing_core_02, bloonsday_pro_p... |
| bloonsday_pulsing_beam | 애니메이션 | 3 | 60x12 | bloonsday_pulsing_beam_01, bloonsday_pulsing_beam_02, bloonsday_pulsing_beam_03 |
| bloonsday_pulsing_core | 애니메이션 | 3 | 60x120 | bloonsday_pulsing_core_01, bloonsday_pulsing_core_02, bloonsday_pulsing_core_03 |
| bloonsday_pyramid | 단일 | 1 | 140x215 |  |
| bloonsday_pyramid_pro | 단일 | 1 | 140x215 |  |
| bloonsday_targeting_sphere | 단일 | 1 | 47x47 |  |
| bloonsday_targeting_sphere_pro | 단일 | 1 | 47x47 |  |

## blue

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| blue_bandana | 단일 | 1 | 82x28 |  |

## bomb

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| bomb_tower | 애니메이션 | 4 | 41x130 | bomb_tower_01, bomb_tower_02, bomb_tower_03, bomb_tower_04 |
| bomb_tower_base_btd1 | 단일 | 1 | 56x111 |  |
| bomb_tower_bomb | 애니메이션 | 3 | 76x101 | bomb_tower_bomb_01, bomb_tower_bomb_02, bomb_tower_bomb_03 |
| bomb_tower_bomb_red | 애니메이션 | 3 | 76x101 | bomb_tower_bomb_red_01, bomb_tower_bomb_red_02, bomb_tower_bomb_red_03 |
| bomb_tower_btd1 | 단일 | 1 | 55x110 |  |
| bomb_tower_cluster | 애니메이션 | 4 | 56x174 | bomb_tower_cluster_01, bomb_tower_cluster_02, bomb_tower_cluster_03, bomb_tow... |
| bomb_tower_cluster_btd1 | 단일 | 1 | 74x148 |  |
| bomb_tower_frag | 애니메이션 | 4 | 26x80 | bomb_tower_frag_01, bomb_tower_frag_02, bomb_tower_frag_03, bomb_tower_frag_04 |
| bomb_tower_frag_btd1 | 단일 | 1 | 56x110 |  |
| bomb_tower_impact | 애니메이션 | 4 | 56x174 | bomb_tower_impact_01, bomb_tower_impact_02, bomb_tower_impact_03, bomb_tower_... |
| bomb_tower_impact_btd1 | 단일 | 1 | 74x148 |  |
| bomb_tower_missile | 애니메이션 | 3 | 34x112 | bomb_tower_missile_01, bomb_tower_missile_02, bomb_tower_missile_03 |
| bomb_tower_missile | 단일 | 1 | 40x149 |  |
| bomb_tower_missile_full | 단일 | 1 | 80x149 |  |
| bomb_tower_missile_full_btd1 | 단일 | 1 | 116x168 |  |
| bomb_tower_moab_assassin | 단일 | 1 | 68x167 |  |
| bomb_tower_moab_assassin_full | 단일 | 1 | 136x167 |  |
| bomb_tower_moab_assassin_full_btd1 | 단일 | 1 | 137x165 |  |
| bomb_tower_moab_mauler | 단일 | 1 | 55x128 |  |
| bomb_tower_moab_mauler_full | 단일 | 1 | 110x128 |  |
| bomb_tower_moab_mauler_full_btd1 | 단일 | 1 | 112x128 |  |
| bomb_tower_muzzle_smoke | 애니메이션 | 4 | 97x68 | bomb_tower_muzzle_smoke_01, bomb_tower_muzzle_smoke_02, bomb_tower_muzzle_smo... |
| bomb_tower_propellent_blue | 단일 | 1 | 70x62 |  |
| bomb_tower_propellent_purple | 단일 | 1 | 70x62 |  |
| bomb_tower_red_ring | 애니메이션 | 4 | 26x46 | bomb_tower_red_ring_01, bomb_tower_red_ring_02, bomb_tower_red_ring_03, bomb_... |
| bomb_tower_red_ring_btd1 | 단일 | 1 | 56x110 |  |
| bomb_tower_silo | 단일 | 1 | 82x164 |  |
| bomb_tower_silo_black | 단일 | 1 | 82x164 |  |
| bomb_tower_silo_btd1 | 단일 | 1 | 84x84 |  |
| bomb_tower_silo_doors | 애니메이션 | 6 | 57x114 | bomb_tower_silo_doors_01, bomb_tower_silo_doors_02, bomb_tower_silo_doors_03,... |
| bomb_tower_silo_doors_01_btd1 | 단일 | 1 | 65x131 |  |
| bomb_tower_silo_doors_02_btd1 | 단일 | 1 | 65x130 |  |
| bomb_tower_silo_doors_03_btd1 | 단일 | 1 | 65x130 |  |
| bomb_tower_silo_doors_04_btd1 | 단일 | 1 | 65x130 |  |
| bomb_tower_silo_doors_05_btd1 | 단일 | 1 | 65x130 |  |
| bomb_tower_silo_doors_06_btd1 | 단일 | 1 | 65x130 |  |
| bomb_tower_silo_doors_green | 애니메이션 | 5 | 57x114 | bomb_tower_silo_doors_green_01, bomb_tower_silo_doors_green_02, bomb_tower_si... |
| bomb_tower_silo_doors_green_01_btd1 | 단일 | 1 | 65x131 |  |
| bomb_tower_silo_doors_green_02_btd1 | 단일 | 1 | 65x130 |  |
| bomb_tower_silo_doors_green_03_btd1 | 단일 | 1 | 65x130 |  |
| bomb_tower_silo_doors_green_04_btd1 | 단일 | 1 | 65x130 |  |
| bomb_tower_silo_doors_green_05_btd1 | 단일 | 1 | 65x130 |  |
| bomb_tower_silo_doors_green_06_btd1 | 단일 | 1 | 65x130 |  |
| bomb_tower_silo_doors_square | 애니메이션 | 6 | 90x180 | bomb_tower_silo_doors_square_01, bomb_tower_silo_doors_square_02, bomb_tower_... |
| bomb_tower_silo_doors_square_green | 애니메이션 | 5 | 90x180 | bomb_tower_silo_doors_square_green_01, bomb_tower_silo_doors_square_green_02,... |
| bomb_tower_silo_green | 단일 | 1 | 82x164 |  |
| bomb_tower_silo_square | 단일 | 1 | 90x180 |  |
| bomb_tower_silo_square_black | 단일 | 1 | 90x180 |  |
| bomb_tower_silo_square_green | 단일 | 1 | 90x180 |  |
| bomb_tower_special_ability_projectile | 단일 | 1 | 59x171 |  |
| bomb_tower_special_ability_projectile_full | 단일 | 1 | 118x171 |  |
| bomb_tower_special_ability_projectile_full_btd1 | 단일 | 1 | 116x168 |  |
| bomb_tower_wheel | 단일 | 1 | 28x73 |  |

## boomerang

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| boomerang | 단일 | 1 | 70x39 |  |
| boomerang_arm | 애니메이션 | 3 | 47x68 | boomerang_arm_01, boomerang_arm_02, boomerang_arm_03 |
| boomerang_bionic_arm | 애니메이션 | 2 | 49x96 | boomerang_bionic_arm_01, boomerang_bionic_arm_02 |
| boomerang_bionic_eye | 단일 | 1 | 33x35 |  |
| boomerang_body | 단일 | 1 | 109x113 |  |
| boomerang_chief_headdress | 단일 | 1 | 150x140 |  |
| boomerang_chieftain_mask | 단일 | 1 | 150x140 |  |
| boomerang_feather_band | 단일 | 1 | 150x140 |  |
| boomerang_feather_headdress | 단일 | 1 | 150x140 |  |
| boomerang_feathers | 단일 | 1 | 150x140 |  |
| boomerang_glaive_lord_cape | 단일 | 1 | 59x64 |  |
| boomerang_glaive_lord_head | 단일 | 1 | 53x91 |  |
| boomerang_glaive_riccochet | 단일 | 1 | 109x113 |  |
| boomerang_glaive_riccochet_arm | 애니메이션 | 3 | 47x68 | boomerang_glaive_riccochet_arm_01, boomerang_glaive_riccochet_arm_02, boomera... |
| boomerang_glaive_thrower | 단일 | 1 | 109x113 |  |
| boomerang_glaive_thrower_arm | 애니메이션 | 3 | 47x68 | boomerang_glaive_thrower_arm_01, boomerang_glaive_thrower_arm_02, boomerang_g... |
| boomerang_horned_headdress | 단일 | 1 | 150x140 |  |
| boomerang_launcher | 단일 | 1 | 78x74 |  |
| boomerang_launcher_wire | 연속셀 | 2 | 78x74 | boomerang_launcher_wire_01 ~ boomerang_launcher_wire_02 |
| boomerang_multi_target | 단일 | 1 | 71x58 |  |
| boomerang_red | 단일 | 1 | 72x39 |  |
| boomerang_red_hot_rangs | 단일 | 1 | 55x47 |  |
| boomerang_sonic_boom | 단일 | 1 | 65x34 |  |
| boomerang_sonic_boom_swoosh | 단일 | 1 | 108x99 |  |
| boomerang_thrower | 단일 | 1 | 56x34 |  |
| boomerang_tribal_arm | 연속셀 | 3 | 47x66 | boomerang_tribal_arm_01 ~ boomerang_tribal_arm_03 |
| boomerang_tribal_mask | 단일 | 1 | 150x140 |  |
| boomerang_triple_circle | 단일 | 1 | 64x44 |  |
| boomerang_warpaint | 단일 | 1 | 150x140 |  |
| boomerang_witch_doctor_mask | 단일 | 1 | 150x140 |  |
| boomerang_zulu_band | 단일 | 1 | 150x140 |  |

## buccaneer

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| buccaneer_aircraft_carrier | 단일 | 1 | 76x293 |  |
| buccaneer_aircraft_carrier_extension | 단일 | 1 | 54x170 |  |
| buccaneer_basic_ship | 단일 | 1 | 63x171 |  |
| buccaneer_cannon | 애니메이션 | 4 | 49x78 | buccaneer_cannon_01, buccaneer_cannon_02, buccaneer_cannon_03, buccaneer_cann... |
| buccaneer_cannon_ship | 단일 | 1 | 98x257 |  |
| buccaneer_crows_nest | 단일 | 1 | 100x101 |  |
| buccaneer_destroyer | 애니메이션 | 2 | 68x81 | buccaneer_destroyer_01, buccaneer_destroyer_02 |
| buccaneer_destroyer | 단일 | 1 | 117x268 |  |
| buccaneer_destroyer_radar | 단일 | 1 | 90x22 |  |
| buccaneer_fast_shooting_flag | 애니메이션 | 4 | 110x108 | buccaneer_fast_shooting_flag_01, buccaneer_fast_shooting_flag_02, buccaneer_f... |
| buccaneer_flag_pole | 단일 | 1 | 98x87 |  |
| buccaneer_grape_shot | 단일 | 1 | 56x48 |  |
| buccaneer_hat | 단일 | 1 | 107x73 |  |
| buccaneer_larger_ship | 단일 | 1 | 98x214 |  |
| buccaneer_monkey_pirates | 단일 | 1 | 98x306 |  |
| buccaneer_monkey_pirates_harpoon | 단일 | 1 | 159x29 |  |
| buccaneer_monkey_pirates_sail | 애니메이션 | 2 | 93x81 | buccaneer_monkey_pirates_sail_01, buccaneer_monkey_pirates_sail_02 |
| buccaneer_sail | 애니메이션 | 2 | 93x82 | buccaneer_sail_01, buccaneer_sail_02 |
| buccaneer_sailor | 단일 | 1 | 77x79 |  |

## camo

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| camo_overlay | 단일 | 1 | 77x97 |  |
| camo_regen_overlay | 단일 | 1 | 117x102 |  |

## candy

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| candy | 단일 | 1 | 136x68 |  |
| candy_base | 단일 | 1 | 188x190 |  |
| candy_box | 단일 | 1 | 98x116 |  |
| candy_castle | 단일 | 1 | 122x274 |  |
| candy_chimney | 연속셀 | 2 | 76x97 | candy_chimney_01 ~ candy_chimney_02 |
| candy_choco_base | 단일 | 1 | 94x94 |  |
| candy_factory | 단일 | 1 | 190x198 |  |
| candy_fence_front | 단일 | 1 | 188x190 |  |
| candy_gumball_machine | 단일 | 1 | 37x45 |  |
| candy_house | 단일 | 1 | 98x245 |  |
| candy_lollies | 단일 | 1 | 61x46 |  |
| candy_store | 단일 | 1 | 95x201 |  |
| candy_store_sign | 단일 | 1 | 144x97 |  |
| candy_tree | 단일 | 1 | 99x140 |  |
| candy_tree_large | 단일 | 1 | 119x163 |  |
| candy_window | 단일 | 1 | 39x31 |  |

## ceramic

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| ceramic | 애니메이션 | 5 | 80x107 | ceramic_01, ceramic_02, ceramic_03, ceramic_04, ceramic_05 |
| ceramic_regen | 애니메이션 | 5 | 119x113 | ceramic_regen_01, ceramic_regen_02, ceramic_regen_03, ceramic_regen_04, ceram... |

## cobra

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| cobra_jacket_base | 단일 | 1 | 98x50 |  |

## confused

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| confused | 애니메이션 | 2 | 107x35 | confused_01, confused_02 |

## confusion

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| confusion_star | 단일 | 1 | 51x57 |  |

## dart

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| dart_monkey_arm | 애니메이션 | 3 | 123x115 | dart_monkey_arm_01, dart_monkey_arm_02, dart_monkey_arm_03 |
| dart_monkey_body | 단일 | 1 | 123x115 |  |
| dart_monkey_btd1 | 연속셀 | 4 | 가변(123x115, 113x120) | dart_monkey_btd1_01 ~ dart_monkey_btd1_04 |
| dart_monkey_btd1_arm | 연속셀 | 3 | 123x115 | dart_monkey_btd1_arm_01 ~ dart_monkey_btd1_arm_03 |
| dart_monkey_btd1_bandana_green | 단일 | 1 | 123x115 |  |
| dart_monkey_btd1_bandana_red | 단일 | 1 | 123x115 |  |
| dart_monkey_btd1_catapult | 단일 | 1 | 65x68 |  |
| dart_monkey_btd1_catapult_arm | 연속셀 | 3 | 56x242 | dart_monkey_btd1_catapult_arm_01 ~ dart_monkey_btd1_catapult_arm_03 |
| dart_monkey_cape | 단일 | 1 | 118x64 |  |
| dart_monkey_catapult | 연속셀 | 2 | 가변(21x32, 37x37) | dart_monkey_catapult_01 ~ dart_monkey_catapult_02 |
| dart_monkey_catapult_body | 단일 | 1 | 109x120 |  |
| dart_monkey_catapult_frame | 단일 | 1 | 65x134 |  |
| dart_monkey_catapult_frame_gold | 단일 | 1 | 130x134 |  |
| dart_monkey_catapult_frame_metal | 단일 | 1 | 130x134 |  |
| dart_monkey_catapult_launcher | 연속셀 | 3 | 가변(56x153, 56x104, 56x113) | dart_monkey_catapult_launcher_01 ~ dart_monkey_catapult_launcher_03 |
| dart_monkey_dart | 단일 | 1 | 24x79 |  |
| dart_monkey_halloween_catapult | 단일 | 1 | 76x153 |  |
| dart_monkey_halloween_catapult_arm | 연속셀 | 3 | 58x241 | dart_monkey_halloween_catapult_arm_01 ~ dart_monkey_halloween_catapult_arm_03 |
| dart_monkey_halloween_frankenmonkey | 단일 | 1 | 109x120 |  |
| dart_monkey_halloween_grim_reaper | 단일 | 1 | 137x138 |  |
| dart_monkey_halloween_grim_reaper_arm | 애니메이션 | 3 | 123x115 | dart_monkey_halloween_grim_reaper_arm_01, dart_monkey_halloween_grim_reaper_a... |
| dart_monkey_halloween_grim_reaper_cloak | 단일 | 1 | 137x138 |  |
| dart_monkey_halloween_mummy | 단일 | 1 | 123x115 |  |
| dart_monkey_halloween_mummy_arm | 애니메이션 | 3 | 123x115 | dart_monkey_halloween_mummy_arm_01, dart_monkey_halloween_mummy_arm_02, dart_... |
| dart_monkey_halloween_skeleton | 단일 | 1 | 120x128 |  |
| dart_monkey_halloween_skeleton_arm | 애니메이션 | 3 | 123x115 | dart_monkey_halloween_skeleton_arm_01, dart_monkey_halloween_skeleton_arm_02,... |
| dart_monkey_halloween_zombie_arm | 애니메이션 | 3 | 123x115 | dart_monkey_halloween_zombie_arm_01, dart_monkey_halloween_zombie_arm_02, dar... |
| dart_monkey_halloween_zombie1 | 단일 | 1 | 123x115 |  |
| dart_monkey_halloween_zombie2 | 단일 | 1 | 123x115 |  |
| dart_monkey_medieval | 연속셀 | 4 | 가변(124x116, 124x134, 100x90, 120x128) | dart_monkey_medieval_01 ~ dart_monkey_medieval_05 |
| dart_monkey_medieval_arm | 애니메이션 | 3 | 124x134 | dart_monkey_medieval_arm_01, dart_monkey_medieval_arm_02, dart_monkey_medieva... |
| dart_monkey_medieval_gold_arm | 애니메이션 | 3 | 124x134 | dart_monkey_medieval_gold_arm_01, dart_monkey_medieval_gold_arm_02, dart_monk... |
| dart_monkey_plume | 연속셀 | 2 | 124x134 | dart_monkey_plume_01 ~ dart_monkey_plume_02 |
| dart_monkeycatapult_helmet | 단일 | 1 | 110x128 |  |

## dartling

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| dartling_gun_bads | 단일 | 1 | 62x139 |  |
| dartling_gun_bads_barrel | 애니메이션 | 2 | 36x17 | dartling_gun_bads_barrel_01, dartling_gun_bads_barrel_02 |
| dartling_gun_bads_hat | 단일 | 1 | 88x72 |  |
| dartling_gun_barrel | 애니메이션 | 2 | 24x117 | dartling_gun_barrel_01, dartling_gun_barrel_02 |
| dartling_gun_blue | 단일 | 1 | 47x144 |  |
| dartling_gun_blue_beret | 단일 | 1 | 89x66 |  |
| dartling_gun_doom_ray_beam | 애니메이션 | 1 | 60x12 | dartling_gun_doom_ray_beam_02 |
| dartling_gun_doom_ray_beam_pulsing | 애니메이션 | 2 | 60x12 | dartling_gun_doom_ray_beam_pulsing_01, dartling_gun_doom_ray_beam_pulsing_02 |
| dartling_gun_doom_ray_core | 애니메이션 | 1 | 60x120 | dartling_gun_doom_ray_core_02 |
| dartling_gun_doom_ray_core_pulsing | 애니메이션 | 2 | 60x120 | dartling_gun_doom_ray_core_pulsing_01, dartling_gun_doom_ray_core_pulsing_02 |
| dartling_gun_green_basic | 단일 | 1 | 47x144 |  |
| dartling_gun_green_beret | 단일 | 1 | 89x66 |  |
| dartling_gun_hydra | 단일 | 1 | 47x96 |  |
| dartling_gun_hydra_barrel | 애니메이션 | 2 | 24x48 | dartling_gun_hydra_barrel_01, dartling_gun_hydra_barrel_02 |
| dartling_gun_laser | 단일 | 1 | 46x115 |  |
| dartling_gun_monkey | 단일 | 1 | 109x115 |  |
| dartling_gun_muzzle_smoke | 애니메이션 | 4 | 46x51 | dartling_gun_muzzle_smoke_01, dartling_gun_muzzle_smoke_02, dartling_gun_muzz... |
| dartling_gun_purple | 단일 | 1 | 47x144 |  |
| dartling_gun_purple_beret | 단일 | 1 | 89x66 |  |
| dartling_gun_ray_of_doom | 단일 | 1 | 47x198 |  |
| dartling_gun_red_beret | 단일 | 1 | 89x66 |  |
| dartling_gun_red_circles | 단일 | 1 | 22x44 |  |
| dartling_gun_red_laser | 단일 | 1 | 47x160 |  |
| dartling_gun_red_monkey | 단일 | 1 | 109x115 |  |
| dartling_gun_rocket | 단일 | 1 | 42x61 |  |

## engineer

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| engineer_arm | 단일 | 1 | 42x24 |  |
| engineer_blue_hat | 단일 | 1 | 44x70 |  |
| engineer_foam | 연속셀 | 4 | 가변(30x76, 40x58, 50x54, 61x60) | engineer_foam_01 ~ engineer_foam_04 |
| engineer_foam_bubble | 단일 | 1 | 45x45 |  |
| engineer_foam_bubble_pop | 단일 | 1 | 67x73 |  |
| engineer_foam_gun | 단일 | 1 | 54x122 |  |
| engineer_foam_puddle | 단일 | 1 | 129x150 |  |
| engineer_green_hat | 단일 | 1 | 44x70 |  |
| engineer_grey_hat_red | 단일 | 1 | 44x70 |  |
| engineer_grey_hat_yellow | 단일 | 1 | 44x70 |  |
| engineer_nail | 단일 | 1 | 9x38 |  |
| engineer_nail_gun | 단일 | 1 | 38x72 |  |
| engineer_orange_hat | 단일 | 1 | 44x70 |  |
| engineer_red_hat | 단일 | 1 | 44x70 |  |
| engineer_spanner | 단일 | 1 | 64x68 |  |
| engineer_trap_box | 단일 | 1 | 141x183 |  |
| engineer_trap_box_full | 단일 | 1 | 141x183 |  |
| engineer_trap_door | 연속셀 | 4 | 가변(36x104, 27x104, 18x104, 9x104) | engineer_trap_door_01 ~ engineer_trap_door_04 |
| engineer_trap_door_interior | 단일 | 1 | 64x64 |  |
| engineer_trap_foot | 단일 | 1 | 30x45 |  |
| engineer_trap_glow | 단일 | 1 | 95x109 |  |
| engineer_white_hat_red | 단일 | 1 | 44x70 |  |
| engineer_white_hat_yellow | 단일 | 1 | 44x70 |  |
| engineer_yellow_hat | 단일 | 1 | 44x70 |  |

## evil

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| evil_monkey_temple_projectile | 애니메이션 | 5 | 200x200 | evil_monkey_temple_projectile_01, evil_monkey_temple_projectile_02, evil_monk... |
| evil_temple_cloud | 단일 | 1 | 191x189 |  |

## explosion

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| explosion | 애니메이션 | 4 | 가변(46x49, 104x110, 218x224, 153x184) | explosion_01, explosion_02, explosion_05, explosion_06 |
| explosion_boom | 단일 | 1 | 269x273 |  |

## firework

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| firework_flame | 단일 | 1 | 70x90 |  |

## fireworks

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| fireworks_base | 단일 | 1 | 48x104 |  |
| fireworks_base_slice | 단일 | 1 | 8x104 |  |
| fireworks_circle_symbol | 단일 | 1 | 90x233 |  |
| fireworks_cone_gold | 단일 | 1 | 48x233 |  |
| fireworks_cone_gold_large | 단일 | 1 | 72x258 |  |
| fireworks_cone_green | 단일 | 1 | 70x258 |  |
| fireworks_cone_orange | 단일 | 1 | 48x233 |  |
| fireworks_cone_purple | 단일 | 1 | 48x233 |  |
| fireworks_cone_red | 단일 | 1 | 48x233 |  |
| fireworks_cone_silver | 단일 | 1 | 48x233 |  |
| fireworks_cone_silver_large | 단일 | 1 | 72x258 |  |
| fireworks_cone_striped | 단일 | 1 | 48x233 |  |
| fireworks_cylinder_gold | 단일 | 1 | 48x233 |  |
| fireworks_cylinder_gold_large | 단일 | 1 | 72x258 |  |
| fireworks_cylinder_orange | 단일 | 1 | 72x258 |  |
| fireworks_cylinder_purple | 단일 | 1 | 48x233 |  |
| fireworks_cylinder_red | 단일 | 1 | 48x233 |  |
| fireworks_cylinder_silver | 단일 | 1 | 48x233 |  |
| fireworks_cylinder_silver_large | 단일 | 1 | 72x258 |  |
| fireworks_cylinder_white | 단일 | 1 | 48x233 |  |
| fireworks_flame_symbol | 단일 | 1 | 96x233 |  |
| fireworks_fuse | 단일 | 1 | 90x233 |  |
| fireworks_hardhat | 단일 | 1 | 57x117 |  |
| fireworks_hardhat_ear_protectors | 단일 | 1 | 57x117 |  |
| fireworks_hardhat_stripes | 단일 | 1 | 114x117 |  |
| fireworks_hardhat_visor | 단일 | 1 | 56x117 |  |
| fireworks_radiation_symbol | 단일 | 1 | 139x258 |  |
| fireworks_skull_symbol | 단일 | 1 | 90x233 |  |
| fireworks_sparkle | 단일 | 1 | 94x94 |  |
| fireworks_stars_symbol | 연속셀 | 3 | 90x233 | fireworks_stars_symbol_01 ~ fireworks_stars_symbol_03 |
| fireworks_stripes | 단일 | 1 | 45x233 |  |
| fireworks_target | 단일 | 1 | 32x32 |  |

## frag

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| frag_shrapnel | 단일 | 1 | 23x38 |  |

## frosted

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| frosted_corners | 단일 | 1 | 116x116 |  |

## general

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| general_shockwave_overlay | 단일 | 1 | 276x276 |  |

## glaive

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| glaive | 단일 | 1 | 100x106 |  |
| glaive_red | 단일 | 1 | 100x106 |  |

## glue

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| glue_effect | 연속셀 | 2 | 82x87 | glue_effect_01 ~ glue_effect_02 |
| glue_effect_regen | 연속셀 | 2 | 121x84 | glue_effect_regen_01 ~ glue_effect_regen_02 |
| glue_gunner_basic | 애니메이션 | 5 | 70x124 | glue_gunner_basic_01, glue_gunner_basic_02, glue_gunner_basic_03, glue_gunner... |
| glue_gunner_bloon_dissolver | 단일 | 1 | 110x81 |  |
| glue_gunner_bloon_dissolver_gauge | 단일 | 1 | 34x34 |  |
| glue_gunner_bloon_liquefier | 단일 | 1 | 110x81 |  |
| glue_gunner_blue_arm | 단일 | 1 | 42x25 |  |
| glue_gunner_body_yellow | 단일 | 1 | 110x81 |  |
| glue_gunner_brown_arm | 단일 | 1 | 42x24 |  |
| glue_gunner_corrosive_glue | 단일 | 1 | 110x81 |  |
| glue_gunner_glue_green | 단일 | 1 | 21x48 |  |
| glue_gunner_glue_hose | 애니메이션 | 5 | 78x133 | glue_gunner_glue_hose_01, glue_gunner_glue_hose_02, glue_gunner_glue_hose_03,... |
| glue_gunner_glue_hose_tank | 단일 | 1 | 116x68 |  |
| glue_gunner_glue_splatter | 단일 | 1 | 110x81 |  |
| glue_gunner_glue_striker_tank | 단일 | 1 | 88x77 |  |
| glue_gunner_glue_yellow | 단일 | 1 | 21x48 |  |
| glue_gunner_green_tank | 단일 | 1 | 62x56 |  |
| glue_gunner_grey_tank | 단일 | 1 | 58x57 |  |
| glue_gunner_purple_arm | 단일 | 1 | 42x25 |  |
| glue_gunner_red_arm | 단일 | 1 | 42x24 |  |
| glue_gunner_yellow_arm | 단일 | 1 | 42x25 |  |
| glue_gunner_yellow_tank | 단일 | 1 | 58x57 |  |
| glue_splatter_green_01 | 단일 | 1 | 251x269 |  |
| glue_splatter_green_02_1 | 단일 | 1 | 112x75 |  |
| glue_splatter_green_02_2 | 단일 | 1 | 79x65 |  |
| glue_splatter_green_02_3 | 단일 | 1 | 87x125 |  |
| glue_splatter_green_02_4 | 단일 | 1 | 90x109 |  |
| glue_splatter_green_03_1 | 단일 | 1 | 55x27 |  |
| glue_splatter_green_03_2 | 단일 | 1 | 33x33 |  |
| glue_splatter_green_03_3 | 단일 | 1 | 20x23 |  |
| glue_splatter_green_03_4 | 단일 | 1 | 7x17 |  |
| glue_splatter_green_03_5 | 단일 | 1 | 27x27 |  |
| glue_splatter_green_03_6 | 단일 | 1 | 50x39 |  |
| glue_splatter_monkey_temple_01 | 단일 | 1 | 359x385 |  |
| glue_splatter_monkey_temple_02_1 | 단일 | 1 | 179x110 |  |
| glue_splatter_monkey_temple_02_2 | 단일 | 1 | 118x94 |  |
| glue_splatter_monkey_temple_02_3 | 단일 | 1 | 124x178 |  |
| glue_splatter_monkey_temple_02_4 | 단일 | 1 | 129x159 |  |
| glue_splatter_monkey_temple_03_1 | 단일 | 1 | 131x125 |  |
| glue_splatter_monkey_temple_03_2 | 단일 | 1 | 71x86 |  |
| glue_splatter_monkey_temple_03_3 | 단일 | 1 | 76x90 |  |
| glue_splatter_monkey_temple_03_4 | 단일 | 1 | 69x73 |  |
| glue_splatter_monkey_temple_03_5 | 단일 | 1 | 83x74 |  |

## golden

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| golden_bloon | 연속셀 | 4 | 101x134 | golden_bloon_01 ~ golden_bloon_04 |
| golden_bloon_crack | 연속셀 | 6 | 102x134 | golden_bloon_crack_01 ~ golden_bloon_crack_06 |
| golden_bloon_particle_glow | 단일 | 1 | 25x25 |  |
| golden_bloon_particle_sparkle | 단일 | 1 | 42x42 |  |

## grape

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| grape | 단일 | 1 | 28x35 |  |

## green

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| green_bandana | 단일 | 1 | 82x27 |  |

## grilled

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| grilled_pineapple | 단일 | 1 | 105x152 |  |

## ground

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| ground_zero_explosion | 연속셀 | 2 | 가변(169x174, 231x244) | ground_zero_explosion_03 ~ ground_zero_explosion_04 |
| ground_zero_scorched_earth | 단일 | 1 | 94x94 |  |
| ground_zero_shockwave | 단일 | 1 | 253x253 |  |

## helicopter

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| helicopter_black_body | 단일 | 1 | 67x300 |  |
| helicopter_black_engine | 단일 | 1 | 91x68 |  |
| helicopter_black_red_engine | 단일 | 1 | 91x68 |  |
| helicopter_blue_rotor | 단일 | 1 | 145x38 |  |
| helicopter_blue_tail_stripes | 단일 | 1 | 30x21 |  |
| helicopter_cannons | 단일 | 1 | 24x60 |  |
| helicopter_chinook_body | 단일 | 1 | 105x357 |  |
| helicopter_green_body | 단일 | 1 | 73x309 |  |
| helicopter_green_engine | 단일 | 1 | 69x68 |  |
| helicopter_green_yellow_engine | 단일 | 1 | 69x68 |  |
| helicopter_grey_blue_engine | 단일 | 1 | 69x68 |  |
| helicopter_grey_body | 단일 | 1 | 73x309 |  |
| helicopter_grey_engine | 단일 | 1 | 69x68 |  |
| helicopter_grey_red_engine | 단일 | 1 | 69x68 |  |
| helicopter_grey_yellow_engine | 단일 | 1 | 69x68 |  |
| helicopter_missile | 단일 | 1 | 40x67 |  |
| helicopter_red_rotor | 단일 | 1 | 28x145 |  |
| helicopter_red_tail_stripes | 단일 | 1 | 30x21 |  |
| helicopter_rotor_middle | 단일 | 1 | 38x38 |  |
| helicopter_yellow_rotor | 단일 | 1 | 144x26 |  |
| helicopter_yellow_tail_stripes | 단일 | 1 | 30x21 |  |

## helipad

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| helipad | 단일 | 1 | 72x72 |  |
| helipad_h | 단일 | 1 | 43x52 |  |
| helipad_h_small | 단일 | 1 | 35x42 |  |
| helipad_small | 단일 | 1 | 59x59 |  |

## hot

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| hot_tacks | 애니메이션 | 10 | 122x91 | hot_tacks_01, hot_tacks_02, hot_tacks_03, hot_tacks_04, hot_tacks_05, hot_tac... |

## ice

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| ice_effect | 단일 | 1 | 90x114 |  |
| ice_effect_regen | 단일 | 1 | 129x120 |  |
| ice_explosion | 애니메이션 | 5 | 가변(46x49, 100x105, 165x182, 207x229, 193x216) | ice_explosion_01, ice_explosion_02, ice_explosion_03, ice_explosion_04, ice_e... |
| ice_shard | 단일 | 1 | 20x80 |  |
| ice_shockwave | 단일 | 1 | 276x276 |  |
| ice_tower_absolute_zero_coat | 단일 | 1 | 113x94 |  |
| ice_tower_absolute_zero_monkey | 단일 | 1 | 106x93 |  |
| ice_tower_absolute_zero_monkey_btd1 | 단일 | 1 | 114x97 |  |
| ice_tower_animated_blizzard | 단일 | 1 | 44x20 |  |
| ice_tower_animated_blizzard_btd1 | 단일 | 1 | 42x18 |  |
| ice_tower_animated_snowflake | 연속셀 | 2 | 가변(66x66, 42x42) | ice_tower_animated_snowflake_01 ~ ice_tower_animated_snowflake_02 |
| ice_tower_animated_snowflake_01_btd1 | 단일 | 1 | 62x62 |  |
| ice_tower_animated_snowflake_02_btd1 | 단일 | 1 | 46x46 |  |
| ice_tower_arm | 애니메이션 | 4 | 79x96 | ice_tower_arm_01, ice_tower_arm_02, ice_tower_arm_03, ice_tower_arm_04 |
| ice_tower_arm | 단일 | 1 | 37x32 |  |
| ice_tower_arm_btd1 | 단일 | 1 | 36x34 |  |
| ice_tower_base | 연속셀 | 4 | 가변(64x64, 94x94) | ice_tower_base_01 ~ ice_tower_base_04 |
| ice_tower_base_01_btd1 | 단일 | 1 | 64x64 |  |
| ice_tower_base_02_btd1 | 단일 | 1 | 64x64 |  |
| ice_tower_base_03_btd1 | 단일 | 1 | 94x94 |  |
| ice_tower_base_04_btd1 | 단일 | 1 | 94x94 |  |
| ice_tower_monkey | 단일 | 1 | 109x113 |  |
| ice_tower_monkey_btd1 | 단일 | 1 | 114x97 |  |
| ice_tower_snowflake_logo | 단일 | 1 | 42x42 |  |
| ice_tower_steam | 단일 | 1 | 68x47 |  |
| ice_tower_viral_frost_monkey | 단일 | 1 | 117x115 |  |
| ice_tower_viral_frost_monkey_btd1 | 단일 | 1 | 114x97 |  |

## juggernaut

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| juggernaut_ball | 애니메이션 | 2 | 140x140 | juggernaut_ball_01, juggernaut_ball_02 |
| juggernaut_halloween_pumpkin | 단일 | 1 | 120x113 |  |

## kick

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| kick_1 | 단일 | 1 | 153x172 |  |
| kick_2 | 단일 | 1 | 153x172 |  |
| kick_bandana | 단일 | 1 | 153x172 |  |
| kick_shockwave | 단일 | 1 | 153x172 |  |

## large

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| large_flare | 단일 | 1 | 58x445 |  |

## lead

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| lead | 단일 | 1 | 80x107 |  |
| lead_fx | 단일 | 1 | 83x79 |  |
| lead_regen | 단일 | 1 | 119x113 |  |

## maelstrom

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| maelstrom_spiral | 단일 | 1 | 224x224 |  |

## meerkat

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| meerkat | 단일 | 1 | 86x108 |  |
| meerkat_base | 단일 | 1 | 111x105 |  |
| meerkat_goggles | 단일 | 1 | 76x39 |  |
| meerkat_pro | 단일 | 1 | 86x108 |  |
| meerkat_pro_goggle | 단일 | 1 | 33x35 |  |
| meerkat_pro_laser | 단일 | 1 | 24x53 |  |

## mm

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| mm_box | 단일 | 1 | 148x148 |  |
| mm_bundle | 단일 | 1 | 112x79 |  |
| mm_wad | 단일 | 1 | 114x74 |  |

## moab

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| moab_eating | 연속셀 | 5 | 가변(209x270, 245x254, 253x231, 308x159, 177x104) | moab_eating_01 ~ moab_eating_05 |
| moab_tail | 애니메이션 | 2 | 가변(78x117, 156x117) | moab_tail_01, moab_tail_02 |
| moab_undamaged | 단일 | 1 | 106x435 |  |

## monkey

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| monkey_ace_biplane | 단일 | 1 | 122x213 |  |
| monkey_ace_ground_zero | 단일 | 1 | 139x265 |  |
| monkey_ace_large_prop | 애니메이션 | 5 | 154x18 | monkey_ace_large_prop_01, monkey_ace_large_prop_02, monkey_ace_large_prop_03,... |
| monkey_ace_neva_miss_targeting | 단일 | 1 | 25x178 |  |
| monkey_ace_operation_dart_storm | 단일 | 1 | 139x265 |  |
| monkey_ace_rapid_fire | 단일 | 1 | 45x70 |  |
| monkey_ace_runway | 단일 | 1 | 232x61 |  |
| monkey_ace_runway_light | 단일 | 1 | 40x39 |  |
| monkey_ace_scarf | 애니메이션 | 3 | 32x57 | monkey_ace_scarf_01, monkey_ace_scarf_02, monkey_ace_scarf_03 |
| monkey_ace_sharper_darts | 단일 | 1 | 122x213 |  |
| monkey_ace_spectre | 단일 | 1 | 204x299 |  |
| monkey_apprentice | 단일 | 1 | 59x109 |  |
| monkey_apprentice_arm | 애니메이션 | 3 | 35x71 | monkey_apprentice_arm_01, monkey_apprentice_arm_02, monkey_apprentice_arm_03 |
| monkey_apprentice_arm_blue | 애니메이션 | 3 | 35x71 | monkey_apprentice_arm_blue_01, monkey_apprentice_arm_blue_02, monkey_apprenti... |
| monkey_apprentice_arm_dblue | 애니메이션 | 3 | 36x72 | monkey_apprentice_arm_dblue_01, monkey_apprentice_arm_dblue_02, monkey_appren... |
| monkey_apprentice_arm_dred | 애니메이션 | 3 | 36x72 | monkey_apprentice_arm_dred_01, monkey_apprentice_arm_dred_02, monkey_apprenti... |
| monkey_apprentice_arm_purple | 애니메이션 | 3 | 36x72 | monkey_apprentice_arm_purple_01, monkey_apprentice_arm_purple_02, monkey_appr... |
| monkey_apprentice_arm_red | 애니메이션 | 3 | 35x71 | monkey_apprentice_arm_red_01, monkey_apprentice_arm_red_02, monkey_apprentice... |
| monkey_apprentice_bearded_wizard | 단일 | 1 | 124x136 |  |
| monkey_apprentice_blue_staff_glow | 단일 | 1 | 60x60 |  |
| monkey_apprentice_cloak | 단일 | 1 | 119x71 |  |
| monkey_apprentice_cloud | 단일 | 1 | 76x144 |  |
| monkey_apprentice_dragon_breath | 단일 | 1 | 59x115 |  |
| monkey_apprentice_dragon_breath | 연속셀 | 5 | 가변(76x122, 124x114, 135x107, 105x111, 101x71) | monkey_apprentice_dragon_breath_01 ~ monkey_apprentice_dragon_breath_05 |
| monkey_apprentice_dragon_breath_flicker_large | 단일 | 1 | 14x22 |  |
| monkey_apprentice_dragon_breath_flicker_small | 단일 | 1 | 10x16 |  |
| monkey_apprentice_dragon_breath_staff | 단일 | 1 | 26x88 |  |
| monkey_apprentice_fire_staff | 연속셀 | 2 | 가변(34x95, 34x96) | monkey_apprentice_fire_staff_01 ~ monkey_apprentice_fire_staff_02 |
| monkey_apprentice_fireball | 애니메이션 | 4 | 48x83 | monkey_apprentice_fireball_01, monkey_apprentice_fireball_02, monkey_apprenti... |
| monkey_apprentice_hat_pattern | 단일 | 1 | 47x46 |  |
| monkey_apprentice_hooded_wizard | 단일 | 1 | 118x128 |  |
| monkey_apprentice_intense_magic | 단일 | 1 | 59x109 |  |
| monkey_apprentice_intense_magic_core_blue | 단일 | 1 | 58x58 |  |
| monkey_apprentice_intense_magic_core_yellow | 단일 | 1 | 58x58 |  |
| monkey_apprentice_intense_magic_rotating_halo_blue | 단일 | 1 | 99x109 |  |
| monkey_apprentice_intense_magic_rotating_halo_yellow | 단일 | 1 | 99x109 |  |
| monkey_apprentice_lightning | 단일 | 1 | 207x30 |  |
| monkey_apprentice_lightning_bolt | 단일 | 1 | 59x115 |  |
| monkey_apprentice_magic_core | 단일 | 1 | 46x46 |  |
| monkey_apprentice_magic_hand_glow | 단일 | 1 | 44x44 |  |
| monkey_apprentice_magic_rotating_halo | 단일 | 1 | 87x84 |  |
| monkey_apprentice_magic_tail | 애니메이션 | 4 | 23x30 | monkey_apprentice_magic_tail_01, monkey_apprentice_magic_tail_02, monkey_appr... |
| monkey_apprentice_phoenix_body | 단일 | 1 | 62x272 |  |
| monkey_apprentice_phoenix_wings | 애니메이션 | 9 | 306x218 | monkey_apprentice_phoenix_wings_01, monkey_apprentice_phoenix_wings_02, monke... |
| monkey_apprentice_red_staff_glow | 단일 | 1 | 60x60 |  |
| monkey_apprentice_star_staff | 연속셀 | 2 | 가변(34x99, 34x100) | monkey_apprentice_star_staff_01 ~ monkey_apprentice_star_staff_02 |
| monkey_apprentice_summon_phoenix | 단일 | 1 | 117x109 |  |
| monkey_apprentice_summon_phoenix_base | 단일 | 1 | 73x73 |  |
| monkey_apprentice_summon_phoenix_fire | 애니메이션 | 4 | 28x37 | monkey_apprentice_summon_phoenix_fire_01, monkey_apprentice_summon_phoenix_fi... |
| monkey_apprentice_summon_phoenix_staff | 단일 | 1 | 30x90 |  |
| monkey_apprentice_summon_whirlwind | 단일 | 1 | 59x115 |  |
| monkey_apprentice_summon_whirlwind_staff | 단일 | 1 | 20x90 |  |
| monkey_apprentice_tempest_tornado | 단일 | 1 | 117x109 |  |
| monkey_apprentice_tempest_tornado_staff | 단일 | 1 | 29x90 |  |
| monkey_apprentice_turban | 단일 | 1 | 124x116 |  |
| monkey_apprentice_turban_cap | 단일 | 1 | 124x116 |  |
| monkey_apprentice_turban_hat | 단일 | 1 | 124x116 |  |
| monkey_apprentice_wizard | 단일 | 1 | 120x116 |  |
| monkey_apprentice_wizard_horned | 단일 | 1 | 144x144 |  |
| monkey_farmer_fork | 단일 | 1 | 82x63 |  |
| monkey_farmer_hat | 단일 | 1 | 53x70 |  |
| monkey_farmer_pro_banana | 단일 | 1 | 106x54 |  |
| monkey_farmer_pro_cannon | 단일 | 1 | 47x103 |  |
| monkey_farmer_pro_cannon_fire | 단일 | 1 | 45x40 |  |
| monkey_farmer_pro_hat | 단일 | 1 | 45x70 |  |
| monkey_farmer_pro_straw | 단일 | 1 | 14x46 |  |
| monkey_tail | 단일 | 1 | 42x34 |  |
| monkey_temple | 단일 | 1 | 167x334 |  |
| monkey_temple_bomb_tower_projectile | 단일 | 1 | 60x118 |  |
| monkey_temple_btd1 | 단일 | 1 | 167x167 |  |
| monkey_temple_evil | 단일 | 1 | 167x334 |  |
| monkey_temple_evil_btd1 | 단일 | 1 | 167x167 |  |
| monkey_temple_evil_head_btd1 | 단일 | 1 | 96x110 |  |
| monkey_temple_glue_tower_projectile | 단일 | 1 | 34x76 |  |
| monkey_temple_head | 단일 | 1 | 105x140 |  |
| monkey_temple_head_btd1 | 단일 | 1 | 96x110 |  |
| monkey_temple_head_evil | 단일 | 1 | 105x140 |  |
| monkey_temple_head_shadow | 단일 | 1 | 80x160 |  |
| monkey_temple_ice_tower_projectile | 단일 | 1 | 72x118 |  |
| monkey_temple_lightning | 단일 | 1 | 562x348 |  |
| monkey_temple_main_projectile | 애니메이션 | 5 | 200x200 | monkey_temple_main_projectile_01, monkey_temple_main_projectile_02, monkey_te... |
| monkey_temple_supermonkey_projectile | 단일 | 1 | 72x72 |  |
| monkey_temple_trap_door | 애니메이션 | 6 | 60x120 | monkey_temple_trap_door_01, monkey_temple_trap_door_02, monkey_temple_trap_do... |
| monkey_village | 단일 | 1 | 80x164 |  |
| monkey_village_beacon | 단일 | 1 | 52x111 |  |
| monkey_village_beacon_dish | 단일 | 1 | 51x62 |  |
| monkey_village_energy_beacon_dish | 단일 | 1 | 51x62 |  |
| monkey_village_eye_closed | 단일 | 1 | 85x85 |  |
| monkey_village_eye_diagonal | 애니메이션 | 2 | 85x85 | monkey_village_eye_diagonal_01, monkey_village_eye_diagonal_02 |
| monkey_village_eye_side | 애니메이션 | 2 | 85x85 | monkey_village_eye_side_01, monkey_village_eye_side_02 |
| monkey_village_eye_straight | 애니메이션 | 2 | 85x85 | monkey_village_eye_straight_01, monkey_village_eye_straight_02 |
| monkey_village_fire | 애니메이션 | 4 | 53x63 | monkey_village_fire_01, monkey_village_fire_02, monkey_village_fire_03, monke... |
| monkey_village_fire_pit_stones | 단일 | 1 | 59x47 |  |
| monkey_village_fort | 단일 | 1 | 69x119 |  |
| monkey_village_intel_bureau | 단일 | 1 | 75x193 |  |
| monkey_village_jungle_drums | 단일 | 1 | 58x58 |  |
| monkey_village_town | 단일 | 1 | 136x249 |  |

## mortar

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| mortar_artillery_monkey | 단일 | 1 | 109x123 |  |
| mortar_big_one_bomb | 단일 | 1 | 52x81 |  |
| mortar_double_green_base | 단일 | 1 | 96x103 |  |
| mortar_double_yellow_stripe | 단일 | 1 | 64x57 |  |
| mortar_flames | 단일 | 1 | 64x90 |  |
| mortar_green_barrel | 단일 | 1 | 36x172 |  |
| mortar_green_base | 단일 | 1 | 100x103 |  |
| mortar_highlight | 단일 | 1 | 33x141 |  |
| mortar_large_reticule | 단일 | 1 | 153x153 |  |
| mortar_monkey | 단일 | 1 | 109x123 |  |
| mortar_red_circle | 단일 | 1 | 44x44 |  |
| mortar_small_reticule | 단일 | 1 | 61x61 |  |
| mortar_star | 단일 | 1 | 44x41 |  |
| mortar_tower_muzzle_flash | 단일 | 1 | 120x140 |  |
| mortar_white_barrel | 단일 | 1 | 72x172 |  |
| mortar_white_base | 단일 | 1 | 100x103 |  |
| mortar_yellow_barrel | 단일 | 1 | 59x172 |  |
| mortar_yellow_base | 단일 | 1 | 146x103 |  |
| mortar_yellow_monkey | 단일 | 1 | 109x123 |  |
| mortar_yellow_stripe | 단일 | 1 | 64x28 |  |

## muzzle

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| muzzle_flash | 단일 | 1 | 78x43 |  |

## napalm

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| napalm | 애니메이션 | 4 | 70x79 | napalm_01, napalm_02, napalm_03, napalm_04 |
| napalm_explosion | 애니메이션 | 5 | 가변(46x50, 104x110, 169x174, 231x244, 218x224) | napalm_explosion_01, napalm_explosion_02, napalm_explosion_03, napalm_explosi... |

## navy

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| navy_admiral_cap_peak | 단일 | 1 | 59x22 |  |
| navy_aircraft_carrier | 단일 | 1 | 112x404 |  |
| navy_bridge | 단일 | 1 | 92x316 |  |
| navy_dinghy | 단일 | 1 | 60x190 |  |
| navy_flag_1.1 | 단일 | 1 | 54x70 |  |
| navy_flag_1.2 | 단일 | 1 | 54x70 |  |
| navy_flag_1.3 | 단일 | 1 | 54x70 |  |
| navy_flag_2.1 | 단일 | 1 | 48x69 |  |
| navy_flag_2.2 | 단일 | 1 | 48x69 |  |
| navy_flag_2.3 | 단일 | 1 | 48x69 |  |
| navy_flag_pole | 단일 | 1 | 57x21 |  |
| navy_gun_barrel | 연속셀 | 4 | 53x32 | navy_gun_barrel_01 ~ navy_gun_barrel_04 |
| navy_gun_base | 단일 | 1 | 43x20 |  |
| navy_gun_base_mid | 단일 | 1 | 43x8 |  |
| navy_gunboat | 단일 | 1 | 70x251 |  |
| navy_harpoon | 단일 | 1 | 82x54 |  |
| navy_harpoon_boat | 단일 | 1 | 92x316 |  |
| navy_harpoon_gun | 단일 | 1 | 49x32 |  |
| navy_hovercraft | 단일 | 1 | 80x252 |  |
| navy_hovercraft_prop | 단일 | 1 | 50x62 |  |
| navy_hull_gradient | 단일 | 1 | 6x88 |  |
| navy_large_guns | 단일 | 1 | 68x216 |  |
| navy_radar | 단일 | 1 | 71x21 |  |
| navy_radar_base | 단일 | 1 | 40x40 |  |
| navy_sailor_hat | 단일 | 1 | 71x62 |  |
| navy_speedboat | 단일 | 1 | 68x196 |  |
| navy_window_reflection | 단일 | 1 | 16x12 |  |

## ninja

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| ninja | 단일 | 1 | 112x112 |  |
| ninja_arm | 애니메이션 | 3 | 63x58 | ninja_arm_01, ninja_arm_02, ninja_arm_03 |
| ninja_bandana | 단일 | 1 | 82x30 |  |
| ninja_black | 단일 | 1 | 112x113 |  |
| ninja_bloonjitsu | 단일 | 1 | 112x115 |  |
| ninja_demon_mask | 단일 | 1 | 124x136 |  |
| ninja_grenade | 단일 | 1 | 24x41 |  |
| ninja_hat | 연속셀 | 2 | 가변(112x112, 124x114) | ninja_hat_01 ~ ninja_hat_02 |
| ninja_helmet | 단일 | 1 | 112x112 |  |
| ninja_hood_mask | 단일 | 1 | 108x120 |  |
| ninja_kabuki_mask | 단일 | 1 | 112x136 |  |
| ninja_sabotage | 단일 | 1 | 82x80 |  |
| ninja_samurai_helmet | 단일 | 1 | 112x114 |  |
| ninja_samurai_helmet_mask | 단일 | 1 | 112x120 |  |
| ninja_throwing_star | 단일 | 1 | 50x50 |  |
| ninja_white | 단일 | 1 | 112x113 |  |

## phoenix

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| phoenix_tail | 단일 | 1 | 72x180 |  |

## pineapple

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| pineapple | 단일 | 1 | 105x152 |  |
| pineapple_text | 연속셀 | 3 | 가변(38x82, 55x78, 47x78) | pineapple_text_01 ~ pineapple_text_03 |

## pirates

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| pirates_harpoon_pop | 단일 | 1 | 140x276 |  |

## plaster

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| plaster | 단일 | 1 | 84x32 |  |

## pontoon

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| pontoon | 단일 | 1 | 104x228 |  |
| pontoon_pro | 단일 | 1 | 122x246 |  |

## pop

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| pop | 단일 | 1 | 170x174 |  |
| pop_and_awe_bomb | 단일 | 1 | 127x215 |  |

## portable

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| portable_lake | 단일 | 1 | 139x284 |  |
| portable_lake_duck | 단일 | 1 | 56x34 |  |
| portable_lake_dust | 애니메이션 | 3 | 가변(155x241, 212x256, 231x273) | portable_lake_dust_01, portable_lake_dust_02, portable_lake_dust_03 |
| portable_lake_pro | 단일 | 1 | 278x284 |  |
| portable_lake_ripples | 단일 | 1 | 42x42 |  |
| portable_lake_tentacle | 애니메이션 | 5 | 가변(38x75, 72x184, 76x264, 74x424, 76x279) | portable_lake_tentacle_01, portable_lake_tentacle_02, portable_lake_tentacle_... |

## purple

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| purple_bandana | 단일 | 1 | 82x28 |  |

## rad

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| rad_body | 단일 | 1 | 24x78 |  |
| rad_body_pro | 단일 | 1 | 36x83 |  |
| rad_egg | 연속셀 | 2 | 32x39 | rad_egg_01 ~ rad_egg_02 |
| rad_egg_dust | 애니메이션 | 4 | 가변(48x48, 82x84, 118x120, 119x129) | rad_egg_dust_01, rad_egg_dust_02, rad_egg_dust_03, rad_egg_dust_04 |
| rad_egg_fragment | 단일 | 1 | 24x18 |  |
| rad_egg_fragment_blurred | 단일 | 1 | 31x26 |  |
| rad_egg_shadow | 단일 | 1 | 22x11 |  |
| rad_foot | 단일 | 1 | 35x42 |  |
| rad_head | 단일 | 1 | 36x112 |  |
| rad_head_pro | 단일 | 1 | 36x112 |  |
| rad_nest | 단일 | 1 | 69x137 |  |
| rad_nest_pro | 단일 | 1 | 69x137 |  |
| rad_wing | 애니메이션 | 8 | 가변(108x80, 82x75, 108x77, 112x62, 89x55, 75x47, 83x40, 91x53) | rad_wing_01, rad_wing_02, rad_wing_03, rad_wing_04, rad_wing_05, rad_wing_06,... |
| rad_wing_pro | 애니메이션 | 8 | 가변(208x96, 154x91, 209x89, 206x74, 169x65, 151x54, 150x47, 170x63) | rad_wing_pro_01, rad_wing_pro_02, rad_wing_pro_03, rad_wing_pro_04, rad_wing_... |

## radoblaster

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| radoblaster | 단일 | 1 | 79x79 |  |

## rainbow

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| rainbow | 단일 | 1 | 80x107 |  |
| rainbow_regen | 단일 | 1 | 119x113 |  |

## red

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| red_bandana | 단일 | 1 | 82x27 |  |

## ring

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| ring_of_fire | 단일 | 1 | 212x212 |  |

## sentry

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| sentry_barrel | 단일 | 1 | 42x30 |  |
| sentry_barrel_red | 단일 | 1 | 63x45 |  |
| sentry_muzzle | 단일 | 1 | 26x32 |  |
| sentry_muzzle_red | 단일 | 1 | 39x89 |  |
| sentry_tripod | 단일 | 1 | 114x113 |  |
| sentry_tripod_red | 단일 | 1 | 170x169 |  |
| sentry_turret | 단일 | 1 | 66x55 |  |
| sentry_turret_red | 단일 | 1 | 147x79 |  |

## shockwave

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| shockwave | 단일 | 1 | 218x218 |  |
| shockwave_dot | 단일 | 1 | 31x31 |  |
| shockwave_standard | 단일 | 1 | 218x218 |  |

## small

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| small_lightning | 단일 | 1 | 179x175 |  |

## smoke

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| smoke | 애니메이션 | 3 | 가변(56x61, 46x62, 27x42) | smoke_01, smoke_02, smoke_03 |

## sniper

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| sniper_arm | 단일 | 1 | 48x36 |  |
| sniper_arm | 애니메이션 | 5 | 21x55 | sniper_arm_01, sniper_arm_02, sniper_arm_03, sniper_arm_04, sniper_arm_05 |
| sniper_basic_rifle | 단일 | 1 | 18x72 |  |
| sniper_basic_rifle_muzzle | 단일 | 1 | 12x15 |  |
| sniper_big_game_hunter | 단일 | 1 | 109x113 |  |
| sniper_blunderbus | 단일 | 1 | 27x97 |  |
| sniper_bolt | 단일 | 1 | 13x8 |  |
| sniper_bolt_action | 단일 | 1 | 11x8 |  |
| sniper_camo_cap_blue | 단일 | 1 | 109x113 |  |
| sniper_camo_cap_green | 단일 | 1 | 109x113 |  |
| sniper_camo_cap_purple | 단일 | 1 | 109x113 |  |
| sniper_camo_cap_red | 단일 | 1 | 109x113 |  |
| sniper_casing | 애니메이션 | 4 | 43x17 | sniper_casing_01, sniper_casing_02, sniper_casing_03, sniper_casing_04 |
| sniper_cripple_moab | 단일 | 1 | 127x121 |  |
| sniper_cripple_moab_muzzle | 단일 | 1 | 28x17 |  |
| sniper_deadly_precision | 단일 | 1 | 89x64 |  |
| sniper_deadly_precision_laser | 단일 | 1 | 6x166 |  |
| sniper_faster_firing | 단일 | 1 | 89x64 |  |
| sniper_full_metal_jacket | 단일 | 1 | 89x64 |  |
| sniper_game_hunter | 단일 | 1 | 109x113 |  |
| sniper_goggles | 단일 | 1 | 76x34 |  |
| sniper_goggles_brass | 단일 | 1 | 76x34 |  |
| sniper_green_hat | 단일 | 1 | 89x64 |  |
| sniper_hunter_cap | 단일 | 1 | 109x113 |  |
| sniper_hunter_hat | 단일 | 1 | 109x113 |  |
| sniper_hunter_muzzle | 단일 | 1 | 20x45 |  |
| sniper_hunter_rifle | 단일 | 1 | 20x88 |  |
| sniper_laser | 단일 | 1 | 6x166 |  |
| sniper_point_five_o | 단일 | 1 | 89x64 |  |
| sniper_semi_auto | 단일 | 1 | 90x70 |  |
| sniper_semi_auto_muzzle | 단일 | 1 | 18x35 |  |
| sniper_shades | 단일 | 1 | 109x113 |  |
| sniper_sight | 단일 | 1 | 20x88 |  |
| sniper_sight_brass | 단일 | 1 | 27x97 |  |
| sniper_supply_drop | 단일 | 1 | 134x120 |  |

## snowball

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| snowball | 연속셀 | 5 | 가변(40x27, 36x24, 45x30, 37x27, 39x20) | snowball_01 ~ snowball_05 |

## spectre

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| spectre_mortar_bomb | 단일 | 1 | 36x71 |  |

## spike

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| spike_factory_base | 단일 | 1 | 66x131 |  |
| spike_factory_base_blue | 단일 | 1 | 66x131 |  |
| spike_factory_base_green | 단일 | 1 | 66x131 |  |
| spike_factory_base_orange | 단일 | 1 | 66x131 |  |
| spike_factory_base_purple | 단일 | 1 | 66x131 |  |
| spike_factory_cog | 애니메이션 | 2 | 46x46 | spike_factory_cog_01, spike_factory_cog_02 |
| spike_factory_feet_black | 단일 | 1 | 76x152 |  |
| spike_factory_feet_blue | 단일 | 1 | 76x152 |  |
| spike_factory_feet_purple | 단일 | 1 | 76x152 |  |
| spike_factory_feet_red | 단일 | 1 | 76x152 |  |
| spike_factory_feet_yellow | 단일 | 1 | 76x152 |  |
| spike_factory_fins | 애니메이션 | 2 | 36x71 | spike_factory_fins_01, spike_factory_fins_02 |
| spike_factory_iris | 애니메이션 | 3 | 71x71 | spike_factory_iris_01, spike_factory_iris_02, spike_factory_iris_03 |
| spike_factory_moab_shredr | 애니메이션 | 4 | 73x73 | spike_factory_moab_shredr_01, spike_factory_moab_shredr_02, spike_factory_moa... |
| spike_factory_spiked_mines | 애니메이션 | 4 | 37x73 | spike_factory_spiked_mines_01, spike_factory_spiked_mines_02, spike_factory_s... |
| spike_factory_spiked_mines_pipes | 단일 | 1 | 36x57 |  |
| spike_factory_storm | 애니메이션 | 4 | 73x73 | spike_factory_storm_01, spike_factory_storm_02, spike_factory_storm_03, spike... |
| spike_factory_white_hot_spikes_base | 단일 | 1 | 66x131 |  |

## spiked

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| spiked_mine | 애니메이션 | 10 | 105x106 | spiked_mine_01, spiked_mine_02, spiked_mine_03, spiked_mine_04, spiked_mine_0... |
| spiked_mine_base | 단일 | 1 | 64x64 |  |
| spiked_mine_skull | 단일 | 1 | 45x46 |  |
| spiked_mine_skull_cover | 단일 | 1 | 105x106 |  |
| spiked_mine_spike | 단일 | 1 | 27x31 |  |

## spikeopult

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| spikeopult_ball | 단일 | 1 | 52x52 |  |
| spikeopult_halloween_skull | 단일 | 1 | 44x50 |  |

## splodey

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| splodey_darts_flash | 단일 | 1 | 78x78 |  |
| splodey_darts_ring | 단일 | 1 | 98x98 |  |

## steampunk

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| steampunk_sub_aerial | 단일 | 1 | 45x19 |  |
| steampunk_sub_ballistic_barrel | 연속셀 | 2 | 27x35 | steampunk_sub_ballistic_barrel_01 ~ steampunk_sub_ballistic_barrel_02 |
| steampunk_sub_brass_bands | 연속셀 | 2 | 48x169 | steampunk_sub_brass_bands_01 ~ steampunk_sub_brass_bands_02 |
| steampunk_sub_bronze_bands | 연속셀 | 2 | 48x169 | steampunk_sub_bronze_bands_01 ~ steampunk_sub_bronze_bands_02 |
| steampunk_sub_engine | 단일 | 1 | 32x36 |  |
| steampunk_sub_fin | 단일 | 1 | 57x67 |  |
| steampunk_sub_goggles | 단일 | 1 | 36x36 |  |
| steampunk_sub_gun_barrel | 연속셀 | 2 | 23x24 | steampunk_sub_gun_barrel_01 ~ steampunk_sub_gun_barrel_02 |
| steampunk_sub_gun_base | 단일 | 1 | 16x25 |  |
| steampunk_sub_gun_base_mid | 단일 | 1 | 8x25 |  |
| steampunk_sub_hatch | 단일 | 1 | 32x64 |  |
| steampunk_sub_hull | 연속셀 | 5 | 가변(48x169, 74x211, 60x236, 64x302, 108x343) | steampunk_sub_hull_01 ~ steampunk_sub_hull_05 |
| steampunk_sub_periscope | 단일 | 1 | 32x34 |  |
| steampunk_sub_porthole | 단일 | 1 | 33x74 |  |
| steampunk_sub_silo | 연속셀 | 4 | 16x33 | steampunk_sub_silo_01 ~ steampunk_sub_silo_04 |
| steampunk_sub_spike | 단일 | 1 | 18x65 |  |
| steampunk_sub_tail | 연속셀 | 2 | 가변(53x40, 57x72) | steampunk_sub_tail_01 ~ steampunk_sub_tail_03 |
| steampunk_sub_tailfin | 단일 | 1 | 23x65 |  |
| steampunk_sub_telescope | 단일 | 1 | 30x53 |  |

## stock

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| stock_bloon | 단일 | 1 | 80x107 |  |
| stock_bloon_highlight | 단일 | 1 | 36x67 |  |
| stock_regen_bloon | 단일 | 1 | 119x113 |  |
| stock_regen_bloon_highlight | 단일 | 1 | 99x54 |  |

## submarine

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| submarine_airburst | 단일 | 1 | 4x48 |  |
| submarine_antenna | 단일 | 1 | 13x34 |  |
| submarine_ballistic_gun | 연속셀 | 3 | 18x40 | submarine_ballistic_gun_01 ~ submarine_ballistic_gun_03 |
| submarine_ballistic_missile | 단일 | 1 | 53x220 |  |
| submarine_barbed_darts | 단일 | 1 | 23x11 |  |
| submarine_base | 단일 | 1 | 52x173 |  |
| submarine_base_waves | 단일 | 1 | 60x190 |  |
| submarine_bay | 연속셀 | 4 | 17x34 | submarine_bay_00 ~ submarine_bay_03 |
| submarine_binocs | 단일 | 1 | 36x38 |  |
| submarine_bloontonium_reactor | 단일 | 1 | 74x282 |  |
| submarine_bmissile | 단일 | 1 | 80x149 |  |
| submarine_dart | 단일 | 1 | 24x79 |  |
| submarine_dart_light | 단일 | 1 | 21x21 |  |
| submarine_first_strike | 단일 | 1 | 73x338 |  |
| submarine_first_strike_missile | 단일 | 1 | 106x197 |  |
| submarine_gun | 연속셀 | 3 | 16x32 | submarine_gun_01 ~ submarine_gun_03 |
| submarine_hat_black | 단일 | 1 | 40x68 |  |
| submarine_hat_blue | 단일 | 1 | 40x68 |  |
| submarine_hat_connery | 단일 | 1 | 31x81 |  |
| submarine_hat_green | 단일 | 1 | 40x68 |  |
| submarine_hat_red | 단일 | 1 | 40x68 |  |
| submarine_hat_white | 단일 | 1 | 40x68 |  |
| submarine_hat_yellow | 단일 | 1 | 40x68 |  |
| submarine_improved_range | 단일 | 1 | 30x69 |  |
| submarine_jet | 단일 | 1 | 29x42 |  |
| submarine_light | 단일 | 1 | 29x29 |  |
| submarine_missile | 단일 | 1 | 19x20 |  |
| submarine_missile_first_strike | 단일 | 1 | 19x20 |  |
| submarine_paint | 단일 | 1 | 43x137 |  |
| submarine_periscope | 단일 | 1 | 12x32 |  |
| submarine_portholes | 단일 | 1 | 17x85 |  |
| submarine_radar_pulse | 단일 | 1 | 100x100 |  |
| submarine_radar_scan | 단일 | 1 | 70x100 |  |
| submarine_radiation | 단일 | 1 | 100x100 |  |
| submarine_ripple | 단일 | 1 | 40x40 |  |
| submarine_stripes | 단일 | 1 | 43x41 |  |
| submarine_submerge | 단일 | 1 | 72x224 |  |
| submarine_twin_gun | 연속셀 | 3 | 34x29 | submarine_twin_gun_01 ~ submarine_twin_gun_03 |

## supermonkey

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| supermonkey | 단일 | 1 | 61x100 |  |
| supermonkey_arm | 단일 | 1 | 21x58 |  |
| supermonkey_arm | 애니메이션 | 2 | 43x97 | supermonkey_arm_01, supermonkey_arm_02 |
| supermonkey_arm_btd1 | 단일 | 1 | 22x57 |  |
| supermonkey_arm_medieval | 단일 | 1 | 21x58 |  |
| supermonkey_arm1_btd1 | 단일 | 1 | 46x99 |  |
| supermonkey_arm2_btd1 | 단일 | 1 | 46x99 |  |
| supermonkey_btd1 | 단일 | 1 | 123x99 |  |
| supermonkey_cape_green | 단일 | 1 | 44x61 |  |
| supermonkey_cape_logo | 단일 | 1 | 37x26 |  |
| supermonkey_cape_logo_medieval | 단일 | 1 | 37x26 |  |
| supermonkey_cape_medieval | 단일 | 1 | 44x62 |  |
| supermonkey_cape_purple | 단일 | 1 | 44x61 |  |
| supermonkey_cape_red | 단일 | 1 | 44x61 |  |
| supermonkey_epic_range | 단일 | 1 | 76x39 |  |
| supermonkey_epic_range_btd1 | 단일 | 1 | 70x26 |  |
| supermonkey_fanclub | 단일 | 1 | 119x128 |  |
| supermonkey_fanclub_cape | 단일 | 1 | 117x64 |  |
| supermonkey_halloween | 단일 | 1 | 114x117 |  |
| supermonkey_laser_vision | 단일 | 1 | 90x43 |  |
| supermonkey_laser_vision_btd1 | 단일 | 1 | 90x32 |  |
| supermonkey_laser_vision_projectile | 단일 | 1 | 72x74 |  |
| supermonkey_laser_vision_projectile_single | 단일 | 1 | 24x74 |  |
| supermonkey_medieval | 단일 | 1 | 62x100 |  |
| supermonkey_plasma_vision | 단일 | 1 | 68x55 |  |
| supermonkey_plasma_vision_btd1 | 단일 | 1 | 70x41 |  |
| supermonkey_plasma_vision_projectile | 단일 | 1 | 98x110 |  |
| supermonkey_robo_arm_btd1 | 단일 | 1 | 24x64 |  |
| supermonkey_robo_btd1 | 단일 | 1 | 123x99 |  |
| supermonkey_robo_monkey | 단일 | 1 | 121x125 |  |
| supermonkey_robo_monkey_arm | 단일 | 1 | 31x83 |  |
| supermonkey_storm_cape | 단일 | 1 | 111x100 |  |
| supermonkey_storm_trail | 단일 | 1 | 719x4 |  |
| supermonkey_sun_god | 단일 | 1 | 210x177 |  |
| supermonkey_sun_god_projectile | 단일 | 1 | 90x64 |  |
| supermonkey_sungod_btd1 | 단일 | 1 | 194x150 |  |
| supermonkey_symbol_green_btd1 | 단일 | 1 | 123x99 |  |
| supermonkey_symbol_purple_btd1 | 단일 | 1 | 123x99 |  |
| supermonkey_symbol_red_btd1 | 단일 | 1 | 123x99 |  |
| supermonkey_tech_terror | 단일 | 1 | 152x152 |  |
| supermonkey_tech_terror_arm | 애니메이션 | 2 | 64x119 | supermonkey_tech_terror_arm_01, supermonkey_tech_terror_arm_02 |
| supermonkey_tech_terror_arm_btd1 | 단일 | 1 | 64x119 |  |
| supermonkey_tech_terror_btd1 | 단일 | 1 | 155x125 |  |
| supermonkey_tech_terror_projectile | 단일 | 1 | 118x131 |  |
| supermonkey_temple_trap_door_btd1 | 단일 | 1 | 60x120 |  |
| supermonkey_temple_trap_door_inner_btd1 | 단일 | 1 | 12x12 |  |

## supply

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| supply_drop_pulse | 단일 | 1 | 121x121 |  |
| supply_drop_radio | 단일 | 1 | 121x121 |  |

## tack

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| tack_shooter_base | 단일 | 1 | 52x104 |  |
| tack_shooter_base_blade_maelstrom_btd1 | 단일 | 1 | 104x104 |  |
| tack_shooter_base_btd1 | 단일 | 1 | 104x104 |  |
| tack_shooter_base_ring_of_fire_btd1 | 단일 | 1 | 104x104 |  |
| tack_shooter_blade_maelstrom | 애니메이션 | 2 | 101x101 | tack_shooter_blade_maelstrom_01, tack_shooter_blade_maelstrom_02 |
| tack_shooter_blade_shooter_base | 단일 | 1 | 101x101 |  |
| tack_shooter_blades | 애니메이션 | 2 | 148x148 | tack_shooter_blades_01, tack_shooter_blades_02 |
| tack_shooter_blades_btd1 | 단일 | 1 | 42x42 |  |
| tack_shooter_even_faster_logo | 단일 | 1 | 60x61 |  |
| tack_shooter_faster_firing | 애니메이션 | 2 | 71x71 | tack_shooter_faster_firing_01, tack_shooter_faster_firing_02 |
| tack_shooter_firing | 애니메이션 | 2 | 71x71 | tack_shooter_firing_01, tack_shooter_firing_02 |
| tack_shooter_ring_of_fire | 애니메이션 | 3 | 71x141 | tack_shooter_ring_of_fire_01, tack_shooter_ring_of_fire_02, tack_shooter_ring... |
| tack_shooter_ring_of_fire_flame | 애니메이션 | 3 | 16x21 | tack_shooter_ring_of_fire_flame_01, tack_shooter_ring_of_fire_flame_02, tack_... |
| tack_shooter_sprayer | 애니메이션 | 2 | 71x71 | tack_shooter_sprayer_01, tack_shooter_sprayer_02 |
| tack_shooter_tack | 단일 | 1 | 18x46 |  |
| tack_shooter_tack_logo | 단일 | 1 | 28x52 |  |
| tack_shooter_tube_01_btd1 | 단일 | 1 | 26x73 |  |
| tack_shooter_tube_02_btd1 | 단일 | 1 | 32x73 |  |
| tack_shooter_tube_03_btd1 | 단일 | 1 | 26x73 |  |
| tack_symbol_btd1 | 단일 | 1 | 18x50 |  |

## tacks

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| tacks | 애니메이션 | 10 | 122x91 | tacks_01, tacks_02, tacks_03, tacks_04, tacks_05, tacks_06, tacks_07, tacks_0... |

## tech

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| tech_terror_energy_ball | 단일 | 1 | 138x138 |  |
| tech_terror_energy_overlay | 단일 | 1 | 262x262 |  |

## tempest

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| tempest_tornado | 애니메이션 | 3 | 328x312 | tempest_tornado_01, tempest_tornado_02, tempest_tornado_03 |

## topgun

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| topgun_monkey_ace_bomber | 단일 | 1 | 204x317 |  |
| topgun_monkey_ace_fighter | 단일 | 1 | 148x248 |  |
| topgun_monkey_ace_fighter_jet | 단일 | 1 | 120x262 |  |
| topgun_monkey_ace_gunship | 단일 | 1 | 164x277 |  |
| topgun_monkey_ace_jet | 단일 | 1 | 144x232 |  |
| topgun_monkey_ace_plane | 단일 | 1 | 128x217 |  |
| topgun_monkey_ace_stealth | 단일 | 1 | 140x295 |  |

## track

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| track_glue | 단일 | 1 | 86x101 |  |

## tribal

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| tribal_turtle | 단일 | 1 | 53x116 |  |
| tribal_turtle_arm | 애니메이션 | 3 | 64x79 | tribal_turtle_arm_01, tribal_turtle_arm_02, tribal_turtle_arm_03 |
| tribal_turtle_coconut | 단일 | 1 | 42x63 |  |
| tribal_turtle_feathers | 단일 | 1 | 66x47 |  |
| tribal_turtle_pro_agent_overlay | 단일 | 1 | 87x113 |  |
| tribal_turtle_spear | 단일 | 1 | 36x120 |  |

## triple

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| triple_darts_bandana | 단일 | 1 | 99x77 |  |

## turret1

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| turret1 | 연속셀 | 4 | 90x136 | turret1_01 ~ turret1_04 |

## turret2

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| turret2 | 연속셀 | 4 | 84x160 | turret2_01 ~ turret2_04 |

## ufo

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| ufo_base | 단일 | 1 | 112x223 |  |
| ufo_blade | 단일 | 1 | 34x37 |  |
| ufo_cockpit | 단일 | 1 | 112x223 |  |
| ufo_engine_base | 단일 | 1 | 41x84 |  |
| ufo_engine_blue | 단일 | 1 | 41x84 |  |
| ufo_engine_red | 단일 | 1 | 41x84 |  |
| ufo_engine_vent | 단일 | 1 | 41x84 |  |
| ufo_engine_yellow | 단일 | 1 | 41x84 |  |
| ufo_gun_barrel | 단일 | 1 | 35x77 |  |
| ufo_gun_base | 단일 | 1 | 35x77 |  |
| ufo_light | 단일 | 1 | 20x20 |  |
| ufo_light_blue | 단일 | 1 | 20x20 |  |
| ufo_light_outer | 단일 | 1 | 24x44 |  |
| ufo_light_outer_blue | 단일 | 1 | 24x44 |  |
| ufo_light_outer_red | 단일 | 1 | 24x44 |  |
| ufo_light_outer_yellow | 단일 | 1 | 24x44 |  |
| ufo_light_red | 단일 | 1 | 20x20 |  |
| ufo_light_yellow | 단일 | 1 | 20x20 |  |
| ufo_pad | 단일 | 1 | 72x72 |  |
| ufo_pilot | 단일 | 1 | 78x66 |  |
| ufo_ring | 단일 | 1 | 131x132 |  |
| ufo_rivet | 단일 | 1 | 8x8 |  |

## village

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| village_music | 연속셀 | 2 | 가변(44x40, 28x40) | village_music_01 ~ village_music_02 |
| village_sonar | 단일 | 1 | 102x102 |  |

## whirlwind

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| whirlwind | 애니메이션 | 3 | 233x223 | whirlwind_01, whirlwind_02, whirlwind_03 |

## white

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| white_bandana | 단일 | 1 | 82x28 |  |
| white_ninja_arm | 애니메이션 | 3 | 가변(63x59, 63x58) | white_ninja_arm_01, white_ninja_arm_02, white_ninja_arm_03 |
| white_smoke | 연속셀 | 4 | 가변(84x86, 152x158, 226x230, 230x248) | white_smoke_01 ~ white_smoke_04 |

## wizard

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| wizard_lord | 단일 | 1 | 125x147 |  |
| wizard_lord_arm | 단일 | 1 | 31x60 |  |
| wizard_lord_blue_cloud | 단일 | 1 | 76x144 |  |
| wizard_lord_green_hat_pattern | 단일 | 1 | 51x61 |  |
| wizard_lord_lightning | 단일 | 1 | 92x168 |  |
| wizard_lord_phoenix_body | 단일 | 1 | 172x388 |  |
| wizard_lord_phoenix_flame | 연속셀 | 5 | 가변(76x122, 124x114, 135x107, 105x111, 101x71) | wizard_lord_phoenix_flame_01 ~ wizard_lord_phoenix_flame_05 |
| wizard_lord_phoenix_flicker_large | 단일 | 1 | 14x22 |  |
| wizard_lord_phoenix_flicker_small | 단일 | 1 | 10x16 |  |
| wizard_lord_staff | 단일 | 1 | 29x90 |  |
| wizard_lord_white_cloud | 단일 | 1 | 76x144 |  |
| wizard_lord_white_hat_pattern | 단일 | 1 | 51x61 |  |

## zebra

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| zebra | 단일 | 1 | 80x107 |  |
| zebra_regen | 단일 | 1 | 119x113 |  |

## zomg

| 이름 | 종류 | 개수 | 크기 | 세부 |
|---|---|---|---|---|
| zomg_eating | 연속셀 | 5 | 가변(516x366, 524x352, 492x287, 412x222, 224x132) | zomg_eating_01 ~ zomg_eating_05 |
| zomg_engine | 단일 | 1 | 168x176 |  |
| zomg_nose | 애니메이션 | 2 | 320x88 | zomg_nose_01, zomg_nose_02 |
| zomg_skull | 애니메이션 | 2 | 가변(76x163, 152x163) | zomg_skull_01, zomg_skull_02 |
| zomg_tail | 애니메이션 | 3 | 가변(155x159, 310x159, 310x158) | zomg_tail_01, zomg_tail_02, zomg_tail_03 |
| zomg_undamaged | 단일 | 1 | 160x608 |  |

