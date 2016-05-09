pdf:
	pdflatex -shell-escape thesis.tex
	# bibtex thesis
	pdflatex -shell-escape thesis.tex
	pdflatex -shell-escape thesis.tex
	
	rm -f thesis.aux thesis.bbl thesis.log thesis.out thesis.toc thesis.blg
