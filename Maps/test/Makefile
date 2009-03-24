MAP_BMP = ./gimp_grid.bmp
MAP_NAME = test_map2

$(MAP_NAME).h $(MAP_NAME).c: $(MAP_BMP)
	@echo ""
	@echo ""
	@echo "----------------------------------------------------------"
	@echo "  Converting backgrounds"
	@echo "----------------------------------------------------------"
	grit $(MAP_BMP) -gB4 -mRtpf -mLs -o test_map2.c
	cp  -fv $(MAP_NAME).{c,h} ../../source/

