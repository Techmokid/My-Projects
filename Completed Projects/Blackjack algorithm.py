import random,operator

class deck:
    totalDeck = ["A","2","3","4","5","6","7","8","9","10","K","Q","J","A","2","3","4","5","6","7","8","9","10","K","Q","J","A","2","3","4","5","6","7","8","9","10","K","Q","J","A","2","3","4","5","6","7","8","9","10","K","Q","J"]
    currentDeck = list(totalDeck)
    def getCardFromDeck(self):
        card = random.choice(self.currentDeck)
        self.currentDeck.remove(card)
        return card
    
    def shuffleDeck(self):
        self.currentDeck = list(self.totalDeck)

class PlayerClass:
    def __init__(self,deck,n):
        self.currentCards = []
        self.standing = False
        self.deck = deck
        self.name = n
    
    def getNextCard(self):
        return self.deck.getCardFromDeck()
    
    def getValueOfCard(self,card):
        if (card.isdigit()):
            return int(card)
        if ((card == "K") or (card == "Q") or (card == "J")):
            return 10
        raise "error"

    def hit(self):
        self.currentCards.append(self.getNextCard())
    
    def stand(self):
        self.standing = True
    
    def getValueOfDeck(self):
        result = [0]
        for i in self.currentCards:
            if (i == "A"):
                temp = list(result)
                result = []
                for y in temp:
                    result.append(y+1)
                    result.append(y+10)
            else:
                looper_1 = 0
                for x in result:
                    result[looper_1] += self.getValueOfCard(i)
                    looper_1 += 1
        
        result_2 = []
        for i in result:
            if (i not in result_2):
                result_2.append(i)
        return result_2
    
    def getLargestValidResult(self):
        largest = -1
        for i in self.getValueOfDeck():
            i = int(i)
            if ((i > largest) and (i < 22)):
                largest = i
        self.deckValue = largest
        return largest

class AutomatedDealer:
    def __init__(self,players):
        self.playersReference = []
        self.Deck = deck()
        self.bust = False
        for i in players:
            self.playersReference.append(AutomatedUser(self.Deck,i))
        
        self.myPlayer = PlayerClass(deck(),"Dealer")
        
        for i in self.playersReference:
            i.userReference.hit()
        self.myPlayer.hit()
        for i in self.playersReference:
            i.userReference.hit()
        self.myPlayer.hit()
    
    def runGame(self):
        DealerHunger = 2
        CurrentNumberOfBeatPlayers = 0
        for i in self.playersReference:
            i.myTurn(self.myPlayer)
        
        self.playersReference.sort(key=operator.attrgetter('userReference.deckValue'))
        for x in self.playersReference:
            if (DealerHunger < CurrentNumberOfBeatPlayers):
                while(x.userReference.getLargestValidResult() > self.myPlayer.getLargestValidResult()):
                    self.myPlayer.hit()
                    print("Dealer Hit")
                    if (self.myPlayer.getLargestValidResult() == -1):
                        print("Dealer Went Bust")
                        x.bust = True
                        break
                else:
                    break
            CurrentNumberOfBeatPlayers += 1
            if (self.myPlayer.getLargestValidResult() == -1):
                print("Dealer Went Bust")
                self.bust = True
        self.displayGameResults()
    
    def winner(self):
        allPlayers = []
        if not self.bust:
            allPlayers = [self.myPlayer]
        for x in self.playersReference:
            if not (x.bust):
                allPlayers.append(x.userReference)
        if (len(allPlayers) == 0):
            return "No-one"
        allPlayers.sort(key=operator.attrgetter('deckValue'))
        return allPlayers[0].name
    
    def displayGameResults(self):
        print()
        for i in self.playersReference:
            if (i.bust):
                print(str(i.userReference.name) + " Went Bust")
        print(str(self.winner()) + " Won")

class AutomatedUser:
    _5_Cards_Wins = False
    
    def __init__(self,deck,name,_5_Cards_Wins=_5_Cards_Wins):
        self._5_Cards_Wins = _5_Cards_Wins
        self.userReference = PlayerClass(deck,name)
        self.bust = False
    
    def myTurn(self,dealer):
        while (self.userReference.getLargestValidResult() < 15):
            print(self.userReference.name + " Hit")
            self.userReference.hit()
            #print(self.userReference.name + " : " + str(self.userReference.currentCards) + " : " + str(self.userReference.getLargestValidResult()))
            if ((len(self.userReference.currentCards) == 5) and self._5_Cards_Wins):
                print(self.userReference.name + " Got 5 Cards")
                break
            if (self.userReference.getLargestValidResult() == -1):
                self.bust = True
                self.userReference.stand()
                print(self.userReference.name + " Bust")
                break
        if not self.bust:
            self.userReference.stand()
            print(self.userReference.name + " Standing")

AD = AutomatedDealer(["Player 1","Player 2","Player 3","Player 4"])
AD.runGame()














































