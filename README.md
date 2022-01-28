# 3ds Friend Account Manager

Do not use this unless you know what you are doing.

I'm not responsible for anything that happens as a result of using this.

## Building

1. Install devkitARM, libctru, [armips](https://github.com/Kingcom/armips), and [flips](https://github.com/Alcaro/Flips)
2. Copy decompressed code.bin files from the friends and act sysmodules in their respective `patches` directories
3. Set `NASC_URL` and `ACCOUNT_URL` environment variables
4. Run `make`

## Credits

Thanks to:

- [libctru](https://github.com/devkitPro/libctru) for the `frda.c` base, homebrew template, and all of the library functions
- All 3ds researchers
