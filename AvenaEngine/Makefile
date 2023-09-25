#add ../../ to all objects files so that subfolders can find them 
OBJ = ../../main.o ../../modes.o\
      ../../gameplay/gameplay.o ../../gameplay/player.o ../../gameplay/road.o ../../gameplay/cheese.o  ../../gameplay/cats.o ../../gameplay/ui.o\
      ../../selectscrn/selectscrn.o\
      ../../mainmenu/mainmenu.o

GAME_NAME = RatChance

export OBJ
export GAME_NAME

DC = fm/DC
PSP = fm/PSP
PC = fm/PC
PSV = fm/PSV

all: 
	$(MAKE) psp
	$(MAKE) dc
	$(MAKE) pc
	$(MAKE) psv
	
clean: 
	$(MAKE) pspclean
	$(MAKE) dcclean
	$(MAKE) pc
	$(MAKE) psvclean
	
dc:
	rm -rf $(DC)/romdisk
	mkdir $(DC)/romdisk
	cp -rf dcAssets/ $(DC)/romdisk/Assets
	cd $(DC) && $(MAKE) -f Makefile.dc
dcclean:
	rm -f $(OBJ)
	cd $(DC) && $(MAKE) -f Makefile.dc clean
dcrun:
	#cp -rf Assets $(DC)/romdisk/
	#. /opt/toolchains/dc/kos/environ.sh
	cd $(DC) && $(MAKE) -f Makefile.dc run
dcrunemu: 
	cd $(DC) && $(MAKE) -f Makefile.dc runemu
	
psp:
	cp -rf dcAssets $(PSP)/Assets
	cd $(PSP) && $(MAKE) -f Makefile.psp
pspclean: 
	rm -f $(OBJ)
	cd $(PSP) && $(MAKE) -f Makefile.psp clean
psprun:
	cp -rf Assets $(PSP)
	cd $(PSP) && $(MAKE) -f Makefile.psp run
	
psv:
	cp -rf Assets $(PSV)
	cd $(PSV) && $(MAKE) -f Makefile.psv
psvclean: 
	rm -f $(OBJ)
	cd $(PSV) && $(MAKE) -f Makefile.psv clean
psvrun:
	cp -rf Assets $(PSV)
	cd $(PSV) && $(MAKE) -f Makefile.psv run
	
ifeq ($(OS), Windows_NT)
pc:
	cp -rf Assets $(PC)/GAME
	cd $(PC) && make.exe -f Makefile.win
pcclean: 
	rm -f $(OBJ)
	cd $(PC) && make.exe -f Makefile.win clean
pcrun:
	cp -rf Assets $(PC)/GAME
	cd $(PC) && make.exe -f Makefile.win run	
else

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
pc:
	cp -rf Assets $(PC)
	cd $(PC) && $(MAKE) -f Makefile.osx
pcclean: 
	rm -f $(OBJ)
	cd $(PC) && $(MAKE) -f Makefile.osx clean
pcrun:
	cp -rf Assets $(PC)
	cd $(PC) && $(MAKE) -f Makefile.osx run	
else
pc:
	cp -rf Assets $(PC)
	cd $(PC) && $(MAKE) -f Makefile.nix
pcclean: 
	rm -f $(OBJ)
	cd $(PC) && $(MAKE) -f Makefile.nix clean
pcrun:
	cp -rf Assets $(PC)
	cd $(PC) && $(MAKE) -f Makefile.nix run	
endif
endif
