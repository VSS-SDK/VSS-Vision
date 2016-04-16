#ifndef CORE_H_
#define CORE_H_

#include "unistd.h"
#include "thread"
#include "Vision.h"
#include "Utils/Zocket/Zocket.h"

class Core{
private:
    Vision vision;

    sirlab::State protoState;
    int idData;
    bool hasNewState;
    
    int guiStatus;
    int visionStatus;
    int strategyStatus;
    int systemStatus;

    thread *visionThread;
    thread *strategyThread;

    vector<Robot> *robot;
    Robot *ball;
    Rect *cut;
    float *rotation;

    vector<string> *strategies;
    string *strategySir;
    string *strategyAdv;

    int *idCam;
    bool *device;
    string *imagePath;
    int typeRun;

    vector<string> logs;
public:
    Core();
    void init();
    void start();

    void updateState();     // Protobuf+ZMQ

    void vision_thread();
    void strategy_thread();

    /*
		- O usuário na GUI, quando clicar no botão Iniciar/Pausar jogo, as funções start/pause serão chamadas
			- Para evitar que o sistema fique processando algo mesmo pausado, a função pause utilizará o artifício thread.block
			- Para retomar a thread será utilizado a função thread.unblock

        (Johnathan)
    */
    int getVisionStatus();
    int getStrategyStatus();
    int getVSSStatus();
    int getTypeRun();

    void startVision();
    void startZocket();
    void startSimulator();
    void startVSS();

    void finishVSS();
    
    void pauseVision();
    void pauseZocket();
    void pauseVSS();

    void getRealWorld();
    void getSimuladorWorld();

    void setDevice(bool *device);
    void setIdCamera(int *id);
    void setImagePath(string *imagePath);
    void setRobots(vector<Robot>*);
    void setBall(Robot*);
    void setRotation(float*);
    void setCut(Rect*);
    void setTypeRun(int);
    void setStrategies(vector<string>*);
    void setStrategySir(string*);
    void setStrategyAdv(string*);

    bool* getDevice();
    int* getIdCamera();
    string* getImagePath();
    vector<Robot>* getRobots();
    Robot* getBall();
    float* getRotation();
    Rect* getCut();

};

#endif 