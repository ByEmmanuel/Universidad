import collections
from random import choice
"""Una namedtuple nos permitira acceder a los atributos u objetos que guardemos en el, mediante su nombre"""
Card = collections.namedtuple("Card",["rank","suit"])

class FrenchDeck:
    # todos los numeros del 2 al 11 más las face carfs son los ranks
    ranks = [str(n) for n in range(2,11)] + list("JQKA")
    # split separa todos los strings que estan separados por espacio en subcadenas
    suits = "spades diamonds clubs hearts".split()

    #constructor de la clase e inicializacion,
    """logica detras: las cartas seran, agregadas por cada suit en suits, se añadira tambien su rango """
    def __init__(self):
        self._cards = [Card(rank, suit) for suit in self.suits
                                        for rank in self.ranks]
    def __len__(self):
        return len(self._cards)

    def __getitem__(self, position):
        return self._cards[position]

    def imprimir_items(self, deck ) -> None:
        print(len(deck))

        print(deck[0])
        # mostrar todas
        print(deck[:])
        # mostrar solo las ultimas 3
        print(deck[-3:])
        print(deck[:3])
        # todas menos la ultima
        print(deck[:-1])
        print(deck[12:13])
        # escoge un elemento al azar
        print(choice(deck))

        print(deck.__getitem__(0))

    def spades_high(self, card):
        suit_values = dict(spades=3, hearts=2, diamonds=1, clubs=1)
        rank_value = FrenchDeck.ranks.index(card.rank)
        return rank_value * len(suit_values) + suit_values[card.suit]

    def retornando_algo(self) -> int:
        return "hola"

if __name__ == '__main__':
    beer_card = Card("7", "diamonds")
    print(beer_card)
    deck = FrenchDeck()
    print(f"longitud baraja = {len(deck)}")
    #deck.imprimir_items(deck)
    # reversed me da la vuelta a la lista
    print(deck.retornando_algo())

    """
    for card in reversed(deck):
        print(card)
    """
    print(Card("8", "Faces") in deck)
    for card in sorted(deck, key=deck.spades_high):
        print(card)





