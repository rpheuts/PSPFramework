all:
	$(MAKE) -C src/core/
	$(MAKE) -C src/boot/
	$(MAKE) -C src/kernelmod/

bootloader:
	$(MAKE) -C src/boot/

core:
	$(MAKE) -C src/core/ clean
	$(MAKE) -C src/core/
	
kernelmodule:
	$(MAKE) -C src/kernelmod/
	
xml:
	@rm -rf src/msbparse/*.o
	$(MAKE) -C src/core/
	
apps:
	@rm -rf src/msbparse/*.o
	@rm -rf src/apps/*.o
	$(MAKE) -C src/core/
	
interface:
	@rm -rf src/msbinterface/*.o
	$(MAKE) -C src/core/
	
clean:
	$(MAKE) -C src/core/ clean
	$(MAKE) -C src/boot/ clean
	
install: $(TARGET)
	@echo "Installing to PSP: /mnt/psp"
	@echo "Mounting psp..."
	@echo "Cleaning psp..."
	@rm -rf /cygdrive/f/psp/game/pspfw*
	@echo "Building kxploited version..."
	@make -sC src/boot/ kxploit
	@echo "Installing..."
	@cp -rf src/boot/pspfw /cygdrive/f/psp/game/
	@cp -rf src/boot/pspfw% /cygdrive/f/psp/game/
	@cp src/core/core.prx /cygdrive/f/pspfw/core.prx
	@cp src/boot/pspfw.elf /cygdrive/f/pspfw/
	@cp src/kernelmod/kernmod.prx /cygdrive/f/pspfw/