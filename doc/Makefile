pdf:
	pdflatex -shell-escape thesis.tex
	bibtex thesis
	pdflatex -shell-escape thesis.tex
	pdflatex -shell-escape thesis.tex
	gs -sDEVICE=pdfwrite -dCompatibilityLevel=1.4 -dPDFSETTINGS=/ebook -dNOPAUSE -dQUIET -dBATCH -sOutputFile=thesis_final.pdf thesis.pdf
	
	rm -f thesis.aux thesis.bbl thesis.log thesis.out thesis.toc thesis.blg
