BMPSDIR = ../../assets/animations
OUTPUTSDIR = out

BMPS = $(notdir $(wildcard $(BMPSDIR)/*.bmp))
OUTPUTS = $(BMPS:.bmp=.txt)

info:
	@echo "Generates a header file for animation data for this project."
	@echo "Enable the Python venv before running make generate."
	@echo "Files processed:"
	@echo $(BMPS)
	@echo "Outputs:"
	@echo $(OUTPUTS)

convert: $(OUTPUTS)

%.txt:
	py bmp_to_hex_array.py $(BMPSDIR)/$(patsubst %.txt,%.bmp,$@) > $(OUTPUTSDIR)/$@


generate: convert
	py generate_header.py

.PHONY = info convert generate