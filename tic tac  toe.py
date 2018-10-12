# TIE-02100 Johdatus ohjelmointiin
# Antti Kumavaara, antti.kumavaara@student.tut.fi, opiskelijanumero: 265844
# Ristinolla
# Status: READY

# Tämä ohjelma aukaisee käyttöliittymän, jossa on 3x3 ruudukko nappeja,
# Uusi peli nappi,Lopeta nappi ja info tekstikenttä pelitilanteesta.
# 3x3 ruudukolla voit pelata 1v1 ristinollaa. Jos joko X tai O saa 3 samaa
# ruutua joko pysty-, vaaka- tai vinosuunnassa, hän voittaa. Jos kumpikaan ei
# voita, peli ilmoittaa tasapelistä.
# Aina kun jotain ruudukon nappia painetaan,
# se deaktivoituu ja vuorrosta riippuen kirjoittaa X:n tai O:n.
# Napit saa takaisin tyhjiksi ja NORMAL tilaan painamalla
# Uusi peli nappia. Pelin voi lopettaa Lopeta napilla.
from tkinter import *
SARAKKEITA = 3  # Vakio sarakkeiden määrälle ruudukossa
RIVEJA = 3  # Vakio rivien määrälle ruudukossa


class Peli:
    # Tämä olio on käyttliittymän olio
    def __init__(self):
        """
        Olion rakentaja
        """
        self.__ikkuna = Tk()    # Importin kutsu
        self.__ikkuna.title("Ristinolla")   # Ikkunan otsikko
        self.__vuoro = 1    # Vuorojen tarkastelu
        self.__kierros = 1  # Kierrosten lukumäärän tarkastelu
        self.__napit = {}   # Kirjasto jossa avain on sen nimi ja arvo on nappi
        self.__paattyyko_peli = FALSE   # Arvo pelin päättymisen tarkasteluun
        self.__info = Label(self.__ikkuna, text="Pelaajan X vuoro",
                            font="Helvetica, 10")   # Tieto pelitilanteesta
        self.__info.grid(row=5, column=1)   # Infon sijoitus

        # Seuraava for loop piirtää ruudukon, nimeää ne ja antaa niille tekstin
        for rivi in range(RIVEJA):
            for sarake in range(SARAKKEITA):
                napin_tunniste = str(rivi) + str(sarake)
                napin_nimi = napin_tunniste

                # Kerrotaan muuttujan nimi defille, niin ei tarvitse käyttää
                # lambdaa. Funktio kertoo siitä, että nappia painetaan.
                def napinpainallus(mika_nappi=napin_nimi):
                    self.ristinolla(mika_nappi)

                # Uuden napin nimeäminen
                uusi_nappi = Button(self.__ikkuna,
                                    text=napin_nimi, font="Helvetica, 20",
                                    command=napinpainallus)
                # Napin sijoitus sanakirjaan
                self.__napit[napin_tunniste] = uusi_nappi

                uusi_nappi.grid(row=rivi, column=sarake, sticky=E+W)
                # Napin sijoitus
                uusi_nappi.config(height=5, width=8, text=" ")
                # Napin koon ja tekstin muokkaaminen

        Button(self.__ikkuna, text="Lopeta",
               font="Helvetica, 10", command=self.__ikkuna.destroy) \
            .grid(row=5, column=2, sticky=W + E)
        # Lopeta napin teko ja sijoitus ikkunaan
        Button(self.__ikkuna, text="Uusi peli",
               font="Helvetica, 10", command=self.restart) \
            .grid(row=5, column=0, sticky=W + E)
        # Uusi peli napin teko ja sijoitus ikkunaan

    def ristinolla(self, painettu_nappi):
        """
        Napinpainallus ruudukossa
        :param painettu_nappi: class
        """
        # Seuraava if lause seuraa voiko nappia painaa
        if self.__napit[painettu_nappi]["text"] == " " and self.__vuoro == 1:
            # Jos nappia voi painaa, korvaa teksti X:llä ja poista se käytöstä
            self.__napit[painettu_nappi].configure(text="X", state=DISABLED)
            # Seuraava if lause tarkistaa, voittiko X
            if self.__napit["00"]["text"] == "X" and \
                    self.__napit["01"]["text"] == "X" and \
                    self.__napit["02"]["text"] == "X" or \
                    self.__napit["00"]["text"] == "X" and \
                    self.__napit["11"]["text"] == "X" and \
                    self.__napit["22"]["text"] == "X" or \
                    self.__napit["00"]["text"] == "X" and \
                    self.__napit["10"]["text"] == "X" and \
                    self.__napit["20"]["text"] == "X" or \
                    self.__napit["01"]["text"] == "X" and \
                    self.__napit["11"]["text"] == "X" and \
                    self.__napit["21"]["text"] == "X" or \
                    self.__napit["02"]["text"] == "X" and \
                    self.__napit["12"]["text"] == "X" and \
                    self.__napit["22"]["text"] == "X" or \
                    self.__napit["10"]["text"] == "X" and \
                    self.__napit["11"]["text"] == "X" and \
                    self.__napit["12"]["text"] == "X" or \
                    self.__napit["20"]["text"] == "X" and \
                    self.__napit["21"]["text"] == "X" and \
                    self.__napit["22"]["text"] == "X" or \
                    self.__napit["20"]["text"] == "X" and \
                    self.__napit["11"]["text"] == "X" and \
                    self.__napit["02"]["text"] == "X":
                # Jos X voitti, vaihda totuusarvo pelin päättyymisestä ja
                # vaihda infon teksti
                self.__paattyyko_peli = TRUE
                self.__info.configure(text="PELAAJA X VOITTI!!!")
            else:
                # Kasvata kierroslaskuria
                self.__kierros += 1

        # Seuraava if lause seuraa voiko nappia painaa
        elif self.__napit[painettu_nappi]["text"] and self.__vuoro == 2:
            # Jos nappia voi painaa, korvaa teksti O:llä ja poista se käytöstä
            self.__info.configure(text="Pelaajan O vuoro")
            self.__napit[painettu_nappi].configure(text="O", state=DISABLED)
            # Seuraava if lause tarkistaa, voittiko O
            if self.__napit["00"]["text"] == "O" and \
                    self.__napit["01"]["text"] == "O" and \
                    self.__napit["02"]["text"] == "O" or \
                    self.__napit["00"]["text"] == "O" and \
                    self.__napit["11"]["text"] == "O" and \
                    self.__napit["22"]["text"] == "O" or \
                    self.__napit["00"]["text"] == "O" and \
                    self.__napit["10"]["text"] == "O" and \
                    self.__napit["20"]["text"] == "O" or \
                    self.__napit["01"]["text"] == "O" and \
                    self.__napit["11"]["text"] == "O" and \
                    self.__napit["21"]["text"] == "O" or \
                    self.__napit["02"]["text"] == "O" and \
                    self.__napit["12"]["text"] == "O" and \
                    self.__napit["22"]["text"] == "O" or \
                    self.__napit["10"]["text"] == "O" and \
                    self.__napit["11"]["text"] == "O" and \
                    self.__napit["12"]["text"] == "O" or \
                    self.__napit["20"]["text"] == "O" and \
                    self.__napit["21"]["text"] == "O" and \
                    self.__napit["22"]["text"] == "O" or \
                    self.__napit["20"]["text"] == "O" and \
                    self.__napit["11"]["text"] == "O" and \
                    self.__napit["02"]["text"] == "O":
                # Jos O voitti, vaihda totuusarvo pelin päättyymisestä ja
                # vaihda infon teksti
                self.__paattyyko_peli = TRUE
                self.__info.configure(text="PELAAJA O VOITTI!!!")
            else:
                # Kasvata kierroslukulaskuria
                self.__kierros += 1

        if self.__paattyyko_peli:
            # Jos paattyyko_peli on tosi, muuta napit DISABLED tilaan
            for nappi in self.__napit.keys():
                self.__napit[nappi].configure(state=DISABLED)

        elif self.__kierros == 10:  # Ilmoita tasapelistä, jos laskuri == 10
            self.__info.configure(text="TASAPELI!")
        elif self.__vuoro == 1:     # Vaihda vuoro pelaajasta 1 kakkoseen
            self.__vuoro = 2    # Vaihda pelaajaksi 2
            self.__info.configure(text="Pelaajan O vuoro")  # Vaihda teksti
        elif self.__vuoro == 2:     # Vaihda vuoro pelaajasta 2 ykköseen
            self.__vuoro = 1    # Vaihda pelaajaksi 1
            self.__info.configure(text="Pelaajan X vuoro")  # Vaihda teksti

    def restart(self):
        """
        Aloittaa pelin alusta
        """
        for nappi in self.__napit.keys():
            # Vaihda jokainen nappi NORMAL tilaan
            self.__napit[nappi].configure(text=" ", state=NORMAL)
        self.__info.configure(text="Pelaajan X vuoro")  # Vaihda infoteksti
        self.__kierros = 1  # Palauta laskuri alkuperäiseen arvoonsa
        self.__vuoro = 1    # Palauta laskuri alkuperäiseen arvoonsa
        self.__paattyyko_peli = FALSE   # Vaihda totuusarvo

    def aloita_peli(self):
        """
        Aloita ikkuna
        """
        self.__ikkuna.mainloop()


def main():
    """
    Kutsuu käyttöliittymän ja aloittaa pelin
    """
    ui = Peli()
    ui.aloita_peli()


main()
