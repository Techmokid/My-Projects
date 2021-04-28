from pyftpdlib.authorizers import DummyAuthorizer
from pyftpdlib.handlers import FTPHandler
from pyftpdlib.servers import FTPServer

authorizer = DummyAuthorizer()
authorizer.add_user("TechmoUnity", "beezChurger", "F:/SaveData", perm="elradfmw")
authorizer.add_anonymous("F:/SaveData", perm="elradfmw")

handler = FTPHandler
handler.authorizer = authorizer

server = FTPServer(("localhost", 21), handler)
server.serve_forever()

#----------------------------------------------------------------

#def sendFile(path):
#    print("Sending")
#
#while(True):
#    if (os.path.isfile(trainingDataPath + "/SaveData/saveLock.loc") == False):
#        f = open(trainingDataPath + "/SaveData/loadLock.loc",'w+')
#        f.close()
#
#        pathToZip = trainingDataPath + "/SaveData/Saved AI Network 1/Best Genome"
#        shutil.make_archive(pathToZip,"zip",pathToZip)
#        sendFile(pathToZip + '.zip')
#        os.remove(pathToZip + ".zip")
#        os.remove(trainingDataPath + "/SaveData/loadLock.loc")
#    time.sleep(15)
