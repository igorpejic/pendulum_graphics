Readme in Croatian language:

![specification](https://raw.github.com/igorpejic/pendulum_graphics/blob/master/specification.png)

Zadatak 3.

Slika iz zadatka je realizirana tako da gornji paralelepiped predstavlja objekt koji visi sa stropa (tj. paralelepiped nije strop).
To znaci da paralelepiped ogranicava prvi cilindar, ali drugi se moze naci iznad paralelepiped.

Koristenjem glPushMatrix i glPopMatrix te translacijama (glTranslatef) i rotacijama (glRotatef) realizira se hijerarhijsko modeliranje kojim se dobiva dvostruko njihalo sa slike.

Ovisno o osi rotacije i smjeru, pri svakom pozivu display funkcije kut rotacije se povecava ili smanjuje za 1.
Time se dobiva animacija.

Kretanje njihala je ograniceno primitivnim collision detectionom uz pomoc bounding sphere za donji cilindar te provjerom x koordinate za gornji cilindar.

Trag donjeg cilindra se dobiva tako da se sprema vektor matrica transformacije koje je donji cilindar prosao te se one iscrtavaju povezujuci vertexe u LINE_STRIP.

Upravljanje programom:
Program se pokrece bez argumenata. U pocetku ni za jedan cilindar nije zadana os rotacije.

s - start animacije
x - stop animacije
q, w, e - mijenajanje osi rotacije gornjeg cilindra
b, n, m - mijenajanje osi rotacije donjeg cilindra
Esc - izlaz

Reference:
Laboratorijske vjezbe
http://www.cplusplus.com/
https://developer.mozilla.org/en-US/docs/Games/Techniques/3D_collision_detection#Sphere_versus_sphere
