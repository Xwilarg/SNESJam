.include "hdr.asm"

.section ".rodata1" superfree

tilfont:
.incbin "pvsneslibfont.pic"

palfont:
.incbin "pvsneslibfont.pal"

.ends

.section ".rodata2" superfree

patterns:
.incbin "map_512_512.pic"
patterns_end:

map:
.incbin "map_512_512.map"
map_end:

palette:
.incbin "map_512_512.pal"

.ends

.section ".rodata3" superfree
gfxpsrite: .incbin "ball.pic"
gfxpsrite_end:

palsprite: .incbin "ball.pal"
.ends