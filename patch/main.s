.3ds
.thumb

.open "code.bin", "code_patched.bin", 0x100000

# Remove permission checks
.org 0x14111a
  b 0x141120

.org 0x141144
  b 0x14114a

# Remove account checks
.org 0x102536
  b 0x102556

.org 0x101968
  b 0x101974

.close


