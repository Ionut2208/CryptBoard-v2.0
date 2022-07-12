CryptBoard este un dispozitiv utilitar pentru cei pasionati de criptarea textelor, sau pentru cei ce doresc sa aprofundeze acest domeniu. Este un dispozitiv bazat pe placutele cu microcontroller de tip Arduino, cu un ecran tactil.
Are 3 moduri principale: Play, Work si Wiki.
Modul Play reprezinta un joc in care playerul isi poate testa cunostiintele legate de diverse cifruri cum sunt Codul Morse, Cifrul Cesar, Cifrul Vigenere si altele, avand atat nivele de criptare, cat si nivele de decriptare.
Modul Work reprezinta o platforma pe care userul poate cripta si decripta diverse texte pe care le doreste el, cu scop de descifrare a textelor criptate, dar si cu scop de a invata mai bine cum functioneaza cifrurile.
Modul Wiki reprezinta exact ceea ce spune si numele, o enciclopedie a cifrurilor prezente pe dispozitiv, prezentandu-se cum functioneaza, fapt insotit si de exemple, pentru o intelegere mai usoara. 

La baza dispozitivului sta dorinta de a creste numarul pasionatilor de criptografie si, mai ales, de a le mentine pasiunea celor interesati deja de acest domeniu. Din cauza faptului ca nu exista pe piata o prezenta semnificativa a dispozitivelor/aplicatiilor dedicate criptografiei, in cea mai mare parte fiind doar site-uri ce cripteaza si decripteaza texte, pasiunea pentru criptare a ajuns intr-un punct critic, fiind reaprinsa doar de un numar mic de influenceri ce, ocazional, ofera puzzle-uri de criptare pentru cei ce doresc sa afle diverse informatii inaintea celorlalti(de exemplu, cantaretul Exploit, cand lansa pe YouTube melodii ce faceau parte din albumul sau "Solitudine", lasa la fiecare sfarsit de clip un cod binar, ce, odata descifrat, il ducea pe cel ce il descifra pe un site unde se aflau fie pasaje muzicale din viitoarele melodii, fie diverse imagini si documente). Cu ajutorul CryptBoard se doreste dezvoltarea comunitatii celor pasionati de criptografie si readucerea acesteia in lumea mainstream. Dispozitivul are potential prin multitudinea de cifruri prezente si prin existenta celor 3 moduri de sine statatoare, fiecare avand un rol foarte bine definit. Astfel, o persoana deja pasionata de criptografie va folosi modul Work pentru criptarea si decriptarea textelor alese de el si modul Play pentru a se juca si a-si dovedi cunostiintele prin depasirea constanta a high score-ului. Pe de alta parte, o persoana ce abia descopera domeniul va folosi in prima instanta modul Wiki pentru a invata cum functioneaza fiecare cifru in parte, iar apoi va testa cat de bine a inteles informatia cu ajutorul modului Play. Astfel, publicul tinta al dispozitivului este reprezentat de cei pasionati de criptografie si de cei ce doresc sa afle mai multe sau sa aprofundeze acest domeniu, indiferent de varsta.
CryptBoard a venit ca o necesitate într-un domeniu foarte slab dezvoltat, având ambiții mărețe de a face criptarea un domeniu ce, dincolo de faptul că are o utilitate extraordinară, de la criptare pornind securitatea cibernetică, are și o parte distractiva ce poate fi explorată foarte bine cu ajutorul acestui dispozitiv prin modul Play. 

Inovația dispozitivului sta in faptul că este o adevărată platforma in care utilizatorul poate învăța criptarea folosindu-se de cele 3 funcții principale, având rol utilitar din faptul că se combina utilul, reprezentat de învatarea criptării, cu plăcutul, prin gaming:
Prin modul Play criptarea se învață într-un mod distractiv, dorința de învățare fiind amplificată de dorința gamerilor de a-și depăși constant limitele.
Prin modul Work, utilizatorul poate introduce diverse texte, unele mai scurte, altele mai lungi, unele mai simple, altele mai complexe, toate învațandu-l cum funcționează acel cifru.
Prin modul Wiki, cifrurile sunt prezentate din punct de vedere al metodei de criptare, fiind date și exemple pentru fiecare în parte.
Pentru o experiență cât mai completă, cele 3 moduri trebuie îmbinate constant într-o manieră cat mai egală. 

Concurenta pe piata este ca și inexistentă, accentul pe domeniul criptografic nefiind pus aproape deloc, fie din lipsa de potențiali clienți, fie din lipsa de idei inovative. Însă toate acestea duc la un cerc vicios: fara dispozitive nu apar clienți, iar fara clienți nu exista cerere pentru dispozitive. CryptBoard iese din tipare, fiind un dispozitiv ce are potențial de a atrage clienții. 

Din punct de vedere tehnic, la baza proiectului sta o placuta cu microcontroller de tip Arduino Mega, ce se afla in stransa legatura cu un ecran tactil cu ajutorul caruia se dau toate comenzile. Astfel, dispozitivul nu se afla intr-o legatura prea stransa cu un computer, singurul rol al computerului pentru un user fiind acela de a incarca programul pe placuta. Toata interactiunea cu dispozitivul are loc prin intermediul ecranului de 2.4 inch, astfel ca, dupa incarcarea codului, dispozitivul poate fi folosit si deconectat de la computer, cu ajutorul unei baterii sau a unei baterii externe ce ii ofera curent. Se recomanda utilizarea dispozitivului impreuna cu pen-ul specific ecranului, cu ajutorul lui acuratetea touch-urilor fiind maxima. 

La baza programului sta limbajul de programare specific placutelor Arduino, bazat intr-o foarte mare masura pe limbajul C++. Pentru design-ul tuturor interfetelor dispozitivului s-au folosit metode din biblioteca MCUFRIEND_kbv, pentru functionalitatea touchscreen s-a folosit biblioteca Adafruit TouchScreen, iar pentru retinerea profilurilor din modul Play s-a folosit biblioteca EEPROM specifica scrierii si citirii datelor din memoria ROM a controllerului, memorie ce nu se goleste la deconectarea sau resetarea acestuia. Diverse fragmente de cod de dimensiuni relativ mici din exemplele bibliotecilor pot fi observate in programul propriu-zis, dar adaptate la functionalitatile specifice dispozitivului. Intregul program a fost scris si rulat cu ajutorul Arduino IDE, fiind postat pe repository cu ajutorul Visual Studio Code, Arduino IDE neavand aceasta optiune. 

Tehnologiile alese se justifică prin portabilitate. Deși aplicația poate fi creată fara probleme sub forma de aplicație desktop, nu este la fel de portabila. Datorita dimensiunilor mici ale plăcuței, ea poate fi dusă oriunde fără nicio dificultate. Cât despre posibilitatea de a fi portat pe mobil, deși argumentul cu portabilitatea nu mai este valabil, justificarea tehnologiilor rămâne prin faptul că ecranul CryptBoard nu are lumina albastra nociva pe care o emit ecranele telefoanelor, deci este și o alternativa mai puțin periculoasă. 

Cele 3 moduri prezente in aplicatie pot fi utilizate foarte usor, interfata fiind intuitiva:
La pornire, dispozitivul incepe cu un mesaj de intampinare. Dupa prezentarea mesajului, utilizatorul trebuie sa dea click pe ecran pentru a trece mai departe. Urmeaza meniul principal din care utilizatorul trebuie sa aleaga ce mod doreste sa utilizeze, apasand pe cercul specific. 
Daca alege modul Play, pe ecran va aparea un meniu din care trebuie aleasa optiunea dorita: Adaugare profil, din care utilizatorul isi va crea un profil nou completand toate campurile, dupa completare intorcandu-se la meniul principal din modul Play, Incarcare profil, de unde utilizatorul alege un profil deja creat si introduce parola, fiind dus apoi la meniul profilului, de unde poate alege sa intre pe modul de Play, de unde alege cifrul si modul, sau sa vada statisticile de high score ale profilului, si Stergere profil, utilizatorul avand posibilitatea de a sterge unul din profilurile existente, dupa stergere intorcandu-se la meniul principal din modul Play, de unde trebuie fie sa creeze alt profil, fie sa se logheze pe un profil deja existent. Odata ce utilizatorul alege cifrul si modul, pe ecran va aparea un mesaj de unde utilizatorul trebuie sa selecteze dificultatea: usor, mediu sau dificl. Apoi, va aparea pe ecran textul ce trebuie criptat/decriptat, un textbox unde va aparea textul introdus si o tastatura pentru a se putea introduce textul. Rolurile butoanelor sunt urmatoarele: butonul "<-" sterge ultimul caracter introdus, butonul "?1" arata tastatura cu cifre si simboluri, si butonul "OK" ce semnifica terminarea introducerii textului. Dupa trimiterea raspunsului, utilizatorul va fi punctat astfel: +10 puncte pentru fiecare caracter corect si -5 puncte pentru fiecare caracter gresit. Daca prin caractere gresite se ajunge la scor sub 0, scorul ramane 0. Pe ecran va aparea punctajul de pe acel nivel si raspunsul corect. Daca exista mai mult de 5 caractere gresite, jocul se incheie. Altfel, se trece automat la urmatorul nivel prin apasarea butonului "NEXT". Daca pe parcursul nivelelor se aduna mai mult de 10 caractere gresite, jocul se incheie si utilizatorul este adus inapoi la meniul cu cifruri. Pentru fiecare cifru exista un high score specfic, facandu-se abstractie de mod, criptare sau decriptare. Dupa adunarea unui anumit numar de puncte, nivelul profilului creste, el incepand cu nivelul 1. Nivelul 1 are ca XP pentru urmatorul nivel 50, odata cu trecerea la nivele mai avansate XP-ul necesar crescand cu cate 5 unitati.
Pentru modurile Work și Wiki nu este nevoie de profil, așa că la apăsarea butoanelor specifice va apărea direct ecranul cu cifruri.
In modul Work, se selectează cifrul și modul, apoi se introduce textul. Daca la apăsarea unei taste apare "Caracter neacceptat" înseamnă că acel caracter nu face parte din lista de caractere ce pot fi folosite cu cifrul și/sau modul selectat. După scrierea textului, se apasă "OK", iar pe ecran va apărea textul criptat/decriptat.
In Modul Wiki, se selectează cifrul, apărând informații despre el și butoane pentru a naviga spre pagina urmatoare, unde este cazul, și butoane de "BACK" ce îl întorc pe utilizator fie la meniul cu cifruri, fie la pagina anterioară legata de acel cifru.
In toate interfețele din toate modurile exista butoane de "BACK" pentru a-i oferi utilizatorului posibilitatea de a reveni la meniul principal în cazul unei apăsări realizate din greșeală sau pentru a revedea o informație deja prezentată.
