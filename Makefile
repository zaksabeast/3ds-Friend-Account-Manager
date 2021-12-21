.PHONY: all patch app clean

all: patch app

patch:
	@armips patch/main.s
	@flips -c code.bin code_patched.bin code.ips

app:
	@$(MAKE) -C app

clean:
	@rm code_patched.bin code.ips
	@$(MAKE) -C app clean
