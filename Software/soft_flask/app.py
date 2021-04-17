# pip install flask-socketio
#set FLASK_APP=app.py
#set FLASK_ENV=development
#set FLASK_DEBUG=1
from flask import Flask,render_template,request
from flask_socketio import SocketIO, emit
import json
from dataclasses import dataclass
from kahoot_api import *

@dataclass
class kahootgame:
    start: bool = False #cureently doing nothing
    id: int = 0 #note id is the data order !!!
    quests: int = 0
    maxquest: int = 0
    
thisGame = kahootgame()
playerScored = {}
playerScore = {}
playerAnswered = {}
playersInGame = {}

MacToName = {"dc:4f:22:10:d0:d":"AN",'dc:4f:22:10:d0:d0':"HOA","dc:4f:22:11:39:c1":"NAM"}

def updatePlayer():
    global thisGame
    global playerScore
    global playerScored
    global playerAnswered
    global playersInGame
    global dataBase
    lst = kc.readData()

    for i in MacToName.keys():
        if i in lst:
            lst[MacToName[i]] = lst.pop(i)

    ##### V2
    if list(lst.keys())[0] not in playerAnswered:
        playerAnswered.update(lst)#kc.readData()) #merge
        playersInGame.update(playerAnswered) #merge
        socketio.emit('updatePlayersAnswered',{'playersAnswered':len(playerAnswered),'playersInGame':len(playersInGame)})

        PlayerLobby = []
        for i in playersInGame.keys():
            PlayerLobby.append({'name':i})

        #update score
        if thisGame.start:
            cransw = dataBase['data'][thisGame.id]['questions'][thisGame.quests]['correct']
            for i in playerAnswered.keys():
                # print(playerAnswered[i],cransw)
                if int(playerAnswered[i]) == int(cransw)-1:
                    #if i not in playerScored.keys():
                        playerScore[i]+=1
                        #playerScored[i] = 1
        # print(playerAnswered,playerScore)
        socketio.emit('updatePlayerLobby',PlayerLobby)
    #######
    # playerAnswered.update(kc.readData()) #merge
    # playersInGame.update(playerAnswered) #merge
    # socketio.emit('updatePlayersAnswered',{'playersAnswered':len(playerAnswered),'playersInGame':len(playersInGame)})

    # PlayerLobby = []
    # for i in playersInGame.keys():
    #     PlayerLobby.append({'name':i})

    # #update score
    # if thisGame.start:
    #     cransw = dataBase['data'][thisGame.id]['questions'][thisGame.quests]['correct']
    #     for i in playerAnswered.keys():
    #         # print(playerAnswered[i],cransw)
    #         if int(playerAnswered[i]) == int(cransw)-1:
    #             if i not in playerScored.keys():
    #                 playerScore[i]+=1
    #                 playerScored[i] = 1
    # # print(playerAnswered,playerScore)
    # socketio.emit('updatePlayerLobby',PlayerLobby)

    #end game if all people answer
    if len(playerAnswered) == len(playersInGame):
        quest = dataBase['data'][thisGame.id]['questions'][thisGame.quests]
        #return player data ... wait i dont get this
        playerData = []
        for i in playerAnswered.keys():
            playerData.append({'gameData':{'answer':playerAnswered[i]+1}})
        # playerData = [{'gameData':{'answer':1}},{'gameData':{'answer':1}}]
        correct = quest['correct'][0]
        socketio.emit('questionOver',(playerData,correct))

kc = kahoot_connect('COM4',updatePlayer)

kc.start()

app = Flask(__name__)
socketio = SocketIO(app)

#DB

dataBase = None
with open('DB/data.txt') as json_file:
    dataBase = json.load(json_file)


@app.route('/')
def index():
    # global playersAnswered
    # playersAnswered+=1
    # socketio.emit('updatePlayersAnswered',{'playersAnswered':playersAnswered,'playersInGame':100})
    return render_template('index.html')

@app.route('/host', methods=['GET'])
def host():
    global thisGame
    global dataBase
    global playerScored
    if request.method == 'GET':
        #update this game
        print("gameID:",request.args.get('id'))
        thisGame.id = int(request.args.get('id'))
        thisGame.maxquest = len(dataBase['data'][thisGame.id]['questions'])
        playerScored = {}
    return render_template('host/index.html')

@app.route('/game')
def game():
    return render_template('host/game/index.html')

@app.route('/quiz-creator')
def create():
    return render_template('create/index.html')

# socket.io

@socketio.on('requestDbNames')
def requestDbNames():
    global dataBase
    data = {}
    for i,d in enumerate(dataBase['data']):
        data[str(i)] = {'name':str(d['name']),'id':str(i)} #note d['id'] is not use
    socketio.emit('gameNamesData',data) #{'0':{'name':"HI",'id':'0'},'1':{'name':"HHH",'id':'002'}}

@socketio.on('newQuiz')
def newQuiz(data):
    #update DB
    global dataBase
    try:
        dataBase['data'].append(data)
    except:
        dataBase['data'] = []
        dataBase['data'].append(data)
    #save DB
    with open('DB/data.txt', 'w') as outfile:
        json.dump(dataBase,outfile)
    socketio.emit("startGameFromCreator",data['id'])

@socketio.on('host-join-game')
def hostjoingame(arg1):
    # do start game ?
    global thisGame
    global dataBase
    global playerAnswered
    global playersInGame
    global playerScore

    playerAnswered  = {}
    
    thisGame.quests = 0
    thisGame.maxquest = len(dataBase['data'][thisGame.id]['questions'])
    quest = dataBase['data'][thisGame.id]['questions'][thisGame.quests]
    emit('gameQuestions', {'q1':quest['question'], 'a1':quest['answers'][0], 
                                                   'a2':quest['answers'][1],
                                                   'a3':quest['answers'][2], 
                                                   'a4':quest['answers'][3], 'correct':quest['correct'][0] ,'playersInGame':len(playersInGame)})
    #reset score
    for i in playersInGame.keys():
        playerScore[i] = 0
    thisGame.start = True

    print('received args: ' + str(arg1))

# nextQuestion

@socketio.on('nextQuestion')
def nextQuestion():
    global thisGame
    global dataBase
    global playersInGame
    global playerScore
    global playerAnswered
    playerAnswered  = {}
    thisGame.quests += 1

    #if end of questions
    if thisGame.maxquest == thisGame.quests:
        thisGame.start = False
        scoreboard = {}

        for e,i in enumerate(playerScore.keys()):
            scoreboard['num'+str(e+1)] = i+"="+str(playerScore[i])
        emit('GameOver',scoreboard) #{'num1':'C','num2':'e','num3':'m','num4':'u','num5':'0'}
        return

    #update questions questionOver
    quest = dataBase['data'][thisGame.id]['questions'][thisGame.quests]
    emit('gameQuestions', {'q1':quest['question'], 'a1':quest['answers'][0], 
                                                'a2':quest['answers'][1],
                                                'a3':quest['answers'][2], 
                                                'a4':quest['answers'][3], 'correct':quest['correct'] ,'playersInGame':len(playersInGame)})

# timeUp
@socketio.on('timeUp')
def timeUp():
    global thisGame
    global dataBase
    global playersInGame
    quest = dataBase['data'][thisGame.id]['questions'][thisGame.quests]
    #return player data ... wait i dont get this
    playerData = []
    for i in playerAnswered.keys():
        playerData.append({'gameData':{'answer':playerAnswered[i]+1}})
    # playerData = [{'gameData':{'answer':1}},{'gameData':{'answer':1}}]
    correct = quest['correct'][0]
    emit('questionOver',(playerData,correct))
    

if __name__ == '__main__':
   socketio.run(app,debug = True,use_reloader=False)
