#!/usr/local/bin/fish

./generate_comparison.py -s data/qapdatsol/scr*.sln results/multiple/scr/scr*.sln -o doc/figures/algorithm/metaheuristic/charts/multiple/scr -f png -a
./generate_comparison.py -s data/qapdatsol/scr*.sln results/multiple/scr/scr*.sln -o doc/figures/algorithm/metaheuristic/charts/multiple/scr -f eps -a
./generate_comparison.py -s data/qapdatsol/rou*.sln results/multiple/rou/rou*.sln -o doc/figures/algorithm/metaheuristic/charts/multiple/rou -f png -a
./generate_comparison.py -s data/qapdatsol/rou*.sln results/multiple/rou/rou*.sln -o doc/figures/algorithm/metaheuristic/charts/multiple/rou -f eps -a
./generate_comparison.py -s data/qapdatsol/nug*.sln results/multiple/nug/nug*.sln -o doc/figures/algorithm/metaheuristic/charts/multiple/nug -f png -a
./generate_comparison.py -s data/qapdatsol/nug*.sln results/multiple/nug/nug*.sln -o doc/figures/algorithm/metaheuristic/charts/multiple/nug -f eps -a
./generate_comparison.py -s data/qapdatsol/lipa*b*.sln results/multiple/lipa/lipa*b*.sln -o doc/figures/algorithm/metaheuristic/charts/multiple/lipab -f png -a
./generate_comparison.py -s data/qapdatsol/lipa*b*.sln results/multiple/lipa/lipa*b*.sln -o doc/figures/algorithm/metaheuristic/charts/multiple/lipab -f eps -a
./generate_comparison.py -s data/qapdatsol/lipa*a*.sln results/multiple/lipa/lipa*a*.sln -o doc/figures/algorithm/metaheuristic/charts/multiple/lipaa -f eps -a
./generate_comparison.py -s data/qapdatsol/lipa*a*.sln results/multiple/lipa/lipa*a*.sln -o doc/figures/algorithm/metaheuristic/charts/multiple/lipaa -f png -a
./generate_comparison.py -s data/qapdatsol/had*.sln results/multiple/had/had*.sln -o doc/figures/algorithm/metaheuristic/charts/multiple/had -f png -a
./generate_comparison.py -s data/qapdatsol/had*.sln results/multiple/had/had*.sln -o doc/figures/algorithm/metaheuristic/charts/multiple/had -f eps -a
./generate_comparison.py -s data/qapdatsol/chr*.sln results/multiple/chr/chr*.sln -o doc/figures/algorithm/metaheuristic/charts/multiple/chr -f eps -a
./generate_comparison.py -s data/qapdatsol/bur*.sln results/multiple/bur/bur*.sln -o doc/figures/algorithm/metaheuristic/charts/multiple/bur -f png -a
./generate_comparison.py -s data/qapdatsol/bur*.sln results/multiple/bur/bur*.sln -o doc/figures/algorithm/metaheuristic/charts/multiple/bur -f eps -a
./generate_comparison.py -s data/qapdatsol/chr*.sln results/multiple/chr/chr*.sln -o doc/figures/algorithm/metaheuristic/charts/multiple/chr -f png -a
./generate_comparison.py -s data/qapdatsol/tai{12a,12b,15a,15b,20a,20b,25b,30b,35b,40b,50b,60a,60b,64c,80a,80b,100b,150b,256c}*.sln results/multiple/tai/tai{12a,12b,15a,15b,20a,20b,25b,30b,35b,40b,50b,60a,60b,64c,80a,80b,100b,150b,256c}*.sln -o doc/figures/algorithm/metaheuristic/charts/multiple/tai -f eps -a
./generate_comparison.py -s data/qapdatsol/tai{12a,12b,15a,15b,20a,20b,25b,30b,35b,40b,50b,60a,60b,64c,80a,80b,100b,150b,256c}*.sln results/multiple/tai/tai{12a,12b,15a,15b,20a,20b,25b,30b,35b,40b,50b,60a,60b,64c,80a,80b,100b,150b,256c}*.sln -o doc/figures/algorithm/metaheuristic/charts/multiple/tai -f png -a
./generate_comparison.py -s data/qapdatsol/sko*.sln results/multiple/sko/sko{81,90,100}*.sln -o doc/figures/algorithm/metaheuristic/charts/multiple/sko -f png -a
./generate_comparison.py -s data/qapdatsol/sko*.sln results/multiple/sko/sko{81,90,100}*.sln -o doc/figures/algorithm/metaheuristic/charts/multiple/sko -f eps -a
