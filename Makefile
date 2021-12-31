.PHONY: all patches app clean

all: patches app

FRIEND_TITLE_ID	:= 0004013000003202
ACT_TITLE_ID	:= 0004013000003802

3DS_OUT	:= out/3ds
LUMA_OUT	:= out/luma/titles
FRIEND_OUT	:= $(LUMA_OUT)/$(FRIEND_TITLE_ID)
ACT_OUT	:= $(LUMA_OUT)/$(ACT_TITLE_ID)

patches:
	@mkdir -p $(FRIEND_OUT) $(ACT_OUT)
	@$(MAKE) -C patches
	@cp -r patches/friends/out/* $(FRIEND_OUT)
	@cp -r patches/act/out/* $(ACT_OUT)

app:
	@$(MAKE) -C app
	@mkdir -p $(3DS_OUT)
	@cp app/*.3dsx $(3DS_OUT)

clean:
	@$(MAKE) -C patches clean
	@$(MAKE) -C app clean
	@rm -rf out
