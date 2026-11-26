.PHONY: paper verify
export SOURCE_DATE_EPOCH := 1795622400
export FORCE_SOURCE_DATE := 1
export TZ := UTC

paper:
	mkdir -p build/paper
	pdflatex -halt-on-error -interaction=nonstopmode -output-directory=build/paper paper/main.tex > build/paper/first-pass.txt
	pdflatex -halt-on-error -interaction=nonstopmode -output-directory=build/paper paper/main.tex > build/paper/second-pass.txt
	cp build/paper/main.pdf paper/main.pdf

verify:
	shasum -a 256 -c MANIFEST.sha256
	sh audit/verify.sh
