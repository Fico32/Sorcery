CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -MMD -Werror=vla
EXEC = sorcery
OBJECTS = main.o Player.o Deck.o Card.o Spell.o Hand.o Ritual.o Minion.o Enchantment.o ascii_graphics.o TextDisplay.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
		${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
		rm ${OBJECTS} ${EXEC} ${DEPENDS}
