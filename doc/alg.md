- dlaczego metahuerystyka?
  - po dlugich obserwacjach i researchu nt sluzowca i qap, uswiadomilismy sobie, ze my nie jestesmy w stanie tak przetrasformowac problem qap aby moglbyc w ogole reprezentowalny jako graf planarny na ktorym mailby sie poruszac sluzowiec

- wymyslelismy algorytm ktory moglby dzialac na sluzowcach, jednak  nie jest on realizowalny w praktyce i nie daje tez zadnych zyskow nad metodami tradycyjnymi
  - wymaga w ramach preprocessingu wczesniejszego wygenerowania wszystkich n! przyporzadkowan
  - dla kazdego z nich ustawiany jest platek owsiany o wielkosci odwrotnie proporcjonalnej do kosztu qap (co wymaga policzenia kosztu)
  - sluzowiec jest wypuszczany w jednym lub kilku miejscach, na podstawie obserwacji mozemy zalozyc ze predzej czy pozniej zatrzymalby sie na najwiekszym platku owsianym
  - oczywiscie taki algorytm nie jest praktyczny - jest to rozwiazywanie problemu qap metoda brute force a jedyne co robilby sluzowiec to realizowal funkcje minimum na takim zbiorze rozwiazan

- algorytm ten pomimo oczywistych wad, zainspirowal nas do stworzenia metaheurystyki inspirowanej sluzowowcami
  - o ile naszym case study jest problem qap, taka metaheurystyka moze byc zastosowana dla wielu problemow optymalizacyjnych
  - algorytm dzieli sie na trzy fazy
    - poczatkowy sampling
     - generowany jest poczatkowy losowy zbior N przydzialow
     - wybierane jest K przydzialow o najmniejszym koszcie
     - kazdy z przydzialow reprezentowany jest przez wirtualne jedzenie ktorego ilosc jest odwrotnie proporcjonalna do funkcji kosztu (najlepszy przydzial z probki reprezentuje jednostkowa ilosc pokarmu)
    - ruch wirtualnego plasmodium
      - na kazdym z K pokarmow umieszczane jest „wirtualne plasmodium”
      - zachowanie takiego plasmodium jest poparte obserwacjami rzeczywistego organizmu
      - plasmodium moze odkryc nowy sasiadujacy pokarm jednak wiaze sie to z kosztem EC (energia potrzebna do wykonania eksploracji otoczenia)
        - sasiadni pokarm rozumie sie w sensie rozwiazania QAP rozniacego sie zamiana miejscami jednej pary (2-OPT)
      - plasmodium moze przeniesc sie na sasiadujacy pokarm ktory dostarczy mu nowej porcji pozywienia jednak to kosztuje CC (energia potrzebna do eksploatacji otoczenia)
      - plasmodium przenosi sie na sasiadujacy pokarm tylko wtedy kiedy takiego pokarmu jest wiecej niz obecnie ono posiada
      - jedno plasmodium moze przebywac jednoczesnie na kilku pokarmach - calkowite przeniesienie sie odbywa sie wtedy gdy najmniejszy obserwowalny sasiad jest i tak wiekszy od aktualnie zajmowanego
        - dzieki temu plasmodium moze jeszcze eksplorowac wczesniejsze okolice, pomimo ruchu w kierunku lepszego rozwiazania
    - odnalezenie rozwiazania
      - rozwiazaniem problemu qap jest takie rozwiazanie na ktorym aktualnie przebywa plasmodium i jego koszt jest najmniejszy (pokarm jest najwiekszy)

  - algorytm posiada wiele parametrow
    - wielkosc poczatkowej proby N - zwiekszenie proby powoduje odnajdowanie „dobrych” rozwiazan na wstepnym etapie
    - ilosc aktywnych plasmodiow K - zwiekszenie liczby plasmodiow powoduje eksploaracje wiekszego horyzontu i zwieksza szanse znalezienia optimum globalnego 
    - koszt eksploracji EC - niski koszt stymuluje do lokalnego przeszukiwania sasiadow, wysoki powoduje preferencje do przeniesienia sie
    - koszt ruchu CC - niski koszt stymuluje do ruchu i globalnego przeszukiwania, zmniejsza przeszukiwanie lokalne
    - energia poczatkowa E - wartosc energii ktora posiada nowe plasmodium niezaleznie od jego polozenia, umozliwia ona ruch i eksploracje nawet gdy poczatkowe polozenie jest maloenergetyczne
    - czas dzialania algorytmu - algorytm odbywa sie w dyskretnych krokach i zatrzymuje sie tylko gdy nie wykonuje sie dalsza optymalizacja lub gdy skonczy sie czas, wiekszy czas dzialania algorytmu umozliwia dokladniejsze przeszukanie przestrzeni rozwiazan

