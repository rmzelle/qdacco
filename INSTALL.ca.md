qdacco

Instruccions generals d'instal�laci�
====================================
Nota pr�via: *Debian i Ubuntu t� paquet de dacco i qdacco.+ Per tant no 
cal compilar-ho, instal�lant el paquet �s suficient. Altres distribucions
podrien tenir el paquet tamb�.

Feu:
``apt-get install qdacco``

Quan executeu qdacco per primer cop, demanar� a l'usuari informaci�
de configuraci� (idioma per defecte, directori de dades, etc.)

Algunes distribucions de qdacco venen ja amb les dades, en aquest cas
ser� suficient presionar "B�" per tal de continuar. Altrament, s'haur�
de seleccionar el directori on hi ha els fitxers Dacco (�s a dir, 
el directori 'dictionaries').

Si es necessiten els fitxers de dades, es poden trobar mitjan�ant:
http://www.catalandictionary.org

Instruccions sistemes Unix
==========================
Per tal de compilar qdacco, en distribucions basades en Debian
es necessiten els seg�ents paquets (els quals tenen un nom similar
en altres distribucions):
libqt4-core
libqt4-dev
libqt4-gui
qt4-dev-tools
cmake

Per tal d'instal�lar-los, es necessita executar (es necessitar� ser root
per fer-ho):
apt-get install libqt4-core libqt4-dev libqt4-gui qt4-dev-tools cmake

Cal descomprimir el fitxer de qdacco (tar -zxvf qdacco-X.tar.bz2) i llavors:
cd qdacco
mkdir build
cd build
cmake ../
make

(Ara, a dins build/gui/qdacco i build/text/textqdacco ja hi ha els programes
que podeu executar)

make install #Si voleu instal�lar-ho a /usr/local/bin i /usr/local/lib
	     #executeu-ho com a root

Atenci�: si voleu executar qdacco des de /usr/local/bin, necessiteu que
/usr/local/lib estigui listat a /etc/ld.so.conf (normalment ja ho �s) i que
executeu ldconfig

Potser voldreu afegir un acc�s directe al teu escriptori o gestor de
finestres.

Nota
====
Per baixar-se els diccionaris:
http://prdownloads.sourceforge.net/dacco/dacco-0.9.zip?download

Podeu comprovar mitjan�ant http://www.catalandictionary.org si
n'hi ha de m�s recents.

A Debian, Ubuntu, etc. hi ha paquets propis.

Festival
========
Festival �s un sintetitzador de veu. Sol estar disponible al paquet
festival. Si el teniu instal�lat qdacco el pot fer servir (veure la
configuraci�) i pronunciar les paraules.

**Llegir 'Instruccions generals d'instal�laci�'

Carles Pina i Estany, 2005, 2006, 2007, 2008, 2011, 2013
carles@pina.cat