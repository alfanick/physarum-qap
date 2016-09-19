pdf: pdf_ebook

pdf_ebook:
	pdflatex -shell-escape --enable-write18 '\def\eop{png} \input{thesis.tex}'
	bibtex thesis
	pdflatex -shell-escape --enable-write18 '\def\eop{png} \input{thesis.tex}'
	pdflatex -shell-escape --enable-write18 '\def\eop{png} \input{thesis.tex}'
	gs -sDEVICE=pdfwrite -dCompatibilityLevel=1.4 -dPDFSETTINGS=/printer -dNOPAUSE -dQUIET -dBATCH -r96 -sOutputFile=thesis_ebook.pdf thesis.pdf
	
	rm -f thesis.pdf
	rm -f thesis.aux thesis.bbl thesis.log thesis.out thesis.toc thesis.blg

pdf_print:
	pdflatex -shell-escape '\def\eop{eps} \input{thesis.tex}'
	bibtex thesis
	pdflatex -shell-escape '\def\eop{eps} \input{thesis.tex}'
	pdflatex -shell-escape '\def\eop{eps} \input{thesis.tex}'
	
	mv thesis.pdf thesis_print.pdf
	rm -f thesis.aux thesis.bbl thesis.log thesis.out thesis.toc thesis.blg
