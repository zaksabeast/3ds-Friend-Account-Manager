.PHONY: all clean

ifeq ($(strip $(ACCOUNT_URL)),)
	$(warning "Please set ACCOUNT_URL in your environment")
endif

all:
	@mkdir -p build out
	@armips src/main.s -strequ ACCOUNT_URL "$(ACCOUNT_URL)"
	@flips -c code.bin build/patched_code.bin out/code.ips

clean:
	@rm -rf build out
