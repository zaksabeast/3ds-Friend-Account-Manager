.3ds
.thumb

.open "code.bin", "code_patched.bin", 0x100000

; Remove account checks
.org 0x102536
  b 0x102556

.org 0x101968
  b 0x101974

.close


