.PHONY: clean All

All:
	@echo ----------Building project:[ VMUtil - Debug ]----------
	@"$(MAKE)" -f "VMUtil.mk"
clean:
	@echo ----------Cleaning project:[ VMUtil - Debug ]----------
	@"$(MAKE)" -f "VMUtil.mk" clean
