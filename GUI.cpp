/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include "GUI.h"

GUI::GUI(){
    name = RELEASE;
    width = 1280;
    height = 720;

    timePlay = device = false;
    useCamera = teamSelected = teamSirOk = teamAdvOk = -1;

    show_window_play = show_warning_window = show_configteam_window = show_status_window =  show_credits_window = false;
    show_test_window = false;

    setCalibrationPosition = false;

    // Posiciona os robôs em campo
    Robot r;
    r.setColorTeam(Pixel(255, 255, 255));
    r.setColorRobot(Pixel(255, 255, 255));
    for(int k = 0 ; k < 2 ; k++){
        for(int i = 0 ; i < 3 ; i++){
            r.setOrientation(btVector3(0, 0, 0));
            r.setPosition(btVector3(300 + (i*50), 350 + (k*50), 0)); 
            r.setId(i);
            robot.push_back(r);
        }
    }

    ball.setColorTeam(Pixel(255, 255, 255));
    ball.setColorRobot(Pixel(255, 255, 255));
    ball.setOrientation(btVector3(0, 0, 0));
    ball.setPosition(btVector3(320, 240, 0)); 
    ball.setId(-1);

    loadAllColors();

    ball.setColorTeam(colors.at(ORANGE));
    ball.setVisionColorTeam(visionColors.at(ORANGE));
    ball.setIdColorTeam(ORANGE);
}

void GUI::init(){
    checkThings();

    guiThread = new thread(bind(&GUI::gui_thread, this));
    coreThread = new thread(bind(&GUI::core_thread, this));

    guiThread->join();
    coreThread->join();
}

void GUI::checkThings(){
    string response;
    string sp;
    int qtdFiles;

    errors.clear();
    getAllDevices();
    getAllImages();

    // Verifica se o sistema encontrou alguma camera conectada
    if(devices.size() == 0){
        show_warning_window = true;
        errors.push_back("Nenhuma câmera foi detectada;");
    }

    // Verifica se o sistema encontrou alguma imagem em disco
    if(images.size() == 0){
        show_warning_window = true;
        errors.push_back("Nenhuma imagem em disco foi detectada;");
    }

    // Verifica se todos os arquivos de cores em HSV estão disponíveis
    response = cmdTerminal("find Data/Vision -name *HSV*");
    sp = "";

    qtdFiles = 0;
    for(int i = 0 ; i < response.size() ; i++){
        if(response[i] == '\n'){
            qtdFiles++;
            sp = ""; 
        }else{
            sp += response[i];
        }
    }

    if(qtdFiles != QTD_COLORS){
        stringstream ss;

        show_warning_window = true;
        ss << "Não foi possível detectar " << QTD_COLORS-qtdFiles << " arquivo(s) de cor(es) em HSV;";
        errors.push_back(ss.str().c_str());
    }



    // Verifica se todos os arquivos de cores em RGB estão disponíveis
    response = cmdTerminal("find Data/Draw -name *RGB*");
    sp = "";

    qtdFiles = 0;
    for(int i = 0 ; i < response.size() ; i++){
        if(response[i] == '\n'){
            qtdFiles++;
            sp = ""; 
        }else{
            sp += response[i];
        }
    }

    if(qtdFiles != QTD_COLORS){
        stringstream ss;

        show_warning_window = true;
        ss << "Não foi possível detectar " << QTD_COLORS-qtdFiles << " arquivo(s) de cor(es) em RGB;";
        errors.push_back(ss.str().c_str());
    }


    // Verifica se o arquivo de rotação está disponível
    response = cmdTerminal("find Data -name *rotation*");
    if(response.size() == 0){
        errors.push_back("Não foi possível detectar o arquivo de rotação;");
    }

    // Verifica se o arquivo de corte está disponível
    response = cmdTerminal("find Data -name *rotation*");
    if(response.size() == 0){
        errors.push_back("Não foi possível detectar o arquivo de corte de imagem;");
    }
}

void GUI::gui_thread(){
    report = false;
    show_window_play = false;
    clear_color = ImColor(50, 50, 50);


    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(1);

    window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
    glfwMakeContextCurrent(window);

    // Setup ImGui binding
    ImGui_ImplGlfw_Init(window, true);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glEnable(GL_DEPTH_TEST); // Depth Testing
    glDepthFunc(GL_LEQUAL);
    glDisable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);

    loop();

    release();
}

void GUI::core_thread(){
    core.init();
}

void GUI::loadAllColors(){
    colors.clear();
    visionColors.clear();

    vector<string> pathColors;
    pathColors.push_back("Data/Draw/orangeRGB.csv");
    pathColors.push_back("Data/Draw/blueRGB.csv");
    pathColors.push_back("Data/Draw/redRGB.csv");
    pathColors.push_back("Data/Draw/pinkRGB.csv");
    pathColors.push_back("Data/Draw/purpleRGB.csv");
    pathColors.push_back("Data/Draw/greenRGB.csv");
    pathColors.push_back("Data/Draw/brownRGB.csv");
    pathColors.push_back("Data/Draw/yellowRGB.csv");

    // Carrega as cores em RGB
    for(int i = 0 ; i < 8 ; i++){
        colors.push_back(crud.loadColor(pathColors.at(i)));
    }

    pathColors.clear();
    pathColors.push_back("Data/Vision/orangeHSV.csv");
    pathColors.push_back("Data/Vision/blueHSV.csv");
    pathColors.push_back("Data/Vision/redHSV.csv");
    pathColors.push_back("Data/Vision/pinkHSV.csv");
    pathColors.push_back("Data/Vision/purpleHSV.csv");
    pathColors.push_back("Data/Vision/greenHSV.csv");
    pathColors.push_back("Data/Vision/brownHSV.csv");
    pathColors.push_back("Data/Vision/yellowHSV.csv");
    pathColors.push_back("Data/Vision/cut.csv");
    pathColors.push_back("Data/Vision/rotation.csv");

    // Carrega as cores em HSV
    for(int i = 0 ; i < 8 ; i++){
        visionColors.push_back(crud.loadVisionColor(pathColors.at(i)));
    }

    cut = crud.loadCut(pathColors.at(8));
    rotation = crud.loadRotation(pathColors.at(9));
}

void GUI::setRobotsDefaultPosition(){
    for(int i = 0 ; i < 6 ; i++){
        robot.at(i).setOrientation(btVector3(0, 30, 0));
        if(i < 3)   robot.at(i).setPosition(btVector3(300 + (i*50), 350, 0));
        else        robot.at(i).setPosition(btVector3(300 + ((i-3)*50), 400, 0));
    }
}

static void error_callback(int error, const char* description){
    fprintf(stderr, "Error %d: %s\n", error, description);
}

void GUI::guiMainMenu(){
    if (ImGui::BeginMainMenuBar()){
        if (ImGui::BeginMenu("VSS")){
            if(useCamera == -1 || teamSirOk == -1 || teamAdvOk == -1){
                ImGui::MenuItem("Jogar", "!OK");
            }else{
                if (ImGui::MenuItem("Jogar")){
                    core.setTypeRun(VSS);
                    
                    // Tem que ser ponteiro, pois isso deixará o fluxo de informação no programa BEM MAIS LEVE.
                    {
                        core.setRobots(&robot);
                        core.setBall(&ball);
                        core.setDevice(&device);
                        core.setIdCamera(&idCamera);
                        core.setImagePath(&pathImage);
                        core.setCut(&cut);
                        core.setRotation(&rotation);
                    }

                    core.start();
                    show_window_play = !show_window_play;
                }
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Times")){
            if (ImGui::MenuItem("Carregar Definição Time 1")){
            }
            if (ImGui::MenuItem("Carregar Definição Time 2")){
            }
            if (ImGui::MenuItem("Criar Definição Time 1")){
                loadAllColors();
                show_configteam_window = true;
                teamSelected = OUR_TEAM;
            }
            if (ImGui::MenuItem("Criar Definição Time 2")){
                loadAllColors();
                show_configteam_window = true;
                teamSelected = ADVERSARY_TEAM;
            }
            ImGui::EndMenu();
        }
        
        if (ImGui::BeginMenu("Calibragem")){
            if (ImGui::BeginMenu("Definir Entrada da Visão")) {
                getAllDevices();
                getAllImages();

                for(int i = 0 ; i < images.size() ; i++){
                    if(images.at(i) == pathImage){
                        if (ImGui::MenuItem(images.at(i).c_str(), "OK")) {
                            pathImage = "";
                            useCamera = -1;
                            device = true;
                        }
                    }else{
                        if (ImGui::MenuItem(images.at(i).c_str())) {
                           pathImage = images.at(i);
                           useCamera = 0;
                           device = false;
                        } 
                    }
                }

                for(int i = 0 ; i < devices.size() ; i++){
                    if(devices.at(i) == pathImage){
                        if (ImGui::MenuItem(devices.at(i).c_str(), "OK")) {
                            pathImage = "";
                            useCamera = -1;
                            device = false;
                        }
                    }else{
                        if (ImGui::MenuItem(devices.at(i).c_str())) {
                           pathImage = devices.at(i);
                           useCamera = 1;
                           device = true;
                           char s = pathImage[pathImage.size()-1];
                           idCamera = toInt(s);
                           //cout << idCamera << endl;
                        } 
                    }
                }

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Calibrar Visão")) {
                if (ImGui::MenuItem("Laranja")){
                    if(useCamera == 0){
                        stringstream ss;

                        ss << "cd Calibration && ./Calibration 0 " << "../" << pathImage << " " << ORANGE << " &";
                        cout << ss.str() << endl;
                        system(ss.str().c_str());
                    }else{
                        stringstream ss;

                        ss << "cd Calibration && ./Calibration 1 " << idCamera << " " << ORANGE << " &";
                        cout << ss.str() << endl;
                        system(ss.str().c_str());
                    } 
                }
                if (ImGui::MenuItem("Azul")){
                    if(useCamera == 0){
                        stringstream ss;

                        ss << "cd Calibration && ./Calibration 0 " << "../" << pathImage << " " << BLUE << " &";
                        system(ss.str().c_str());
                    }else{
                        stringstream ss;

                        ss << "cd Calibration && ./Calibration 1 " << idCamera << " " << BLUE << " &";
                        system(ss.str().c_str());
                    }
                }
                if (ImGui::MenuItem("Amarelo")){
                    if(useCamera == 0){
                        stringstream ss;

                        ss << "cd Calibration && ./Calibration 0 " << "../" << pathImage << " " << YELLOW << " &";
                        system(ss.str().c_str());
                    }else{
                        stringstream ss;

                        ss << "cd Calibration && ./Calibration 1 " << idCamera << " " << YELLOW << " &";
                        system(ss.str().c_str());
                    }
                }
                if (ImGui::MenuItem("Vermelho")){
                    if(useCamera == 0){
                        stringstream ss;

                        ss << "cd Calibration && ./Calibration 0 " << "../" << pathImage << " " << RED << " &";
                        system(ss.str().c_str());
                    }else{
                        stringstream ss;

                        ss << "cd Calibration && ./Calibration 1 " << idCamera << " " << RED << " &";
                        system(ss.str().c_str());
                    }
                }
                if (ImGui::MenuItem("Rosa")){
                    if(useCamera == 0){
                        stringstream ss;

                        ss << "cd Calibration && ./Calibration 0 " << "../" << pathImage << " " << PINK << " &";
                        system(ss.str().c_str());
                    }else{
                        stringstream ss;

                        ss << "cd Calibration && ./Calibration 1 " << idCamera << " " << PINK << " &";
                        system(ss.str().c_str());
                    }
                }
                if (ImGui::MenuItem("Roxo")){
                    if(useCamera == 0){
                        stringstream ss;

                        ss << "cd Calibration && ./Calibration 0 " << "../" << pathImage << " " << PURPLE << " &";
                        system(ss.str().c_str());
                    }else{
                        stringstream ss;

                        ss << "cd Calibration && ./Calibration 1 " << idCamera << " " << PURPLE << " &";
                        system(ss.str().c_str());
                    }
                }
                if (ImGui::MenuItem("Verde")){
                    if(useCamera == 0){
                        stringstream ss;

                        ss << "cd Calibration && ./Calibration 0 " << "../" << pathImage << " " << GREEN << " &";
                        system(ss.str().c_str());
                    }else{
                        stringstream ss;

                        ss << "cd Calibration && ./Calibration 1 " << idCamera << " " << GREEN << " &";
                        system(ss.str().c_str());
                    }
                }
                if (ImGui::MenuItem("Marrom")){
                    if(useCamera == 0){
                        stringstream ss;

                        ss << "cd Calibration && ./Calibration 0 " << "../" << pathImage << " " << BROWN << " &";
                        system(ss.str().c_str());
                    }else{
                        stringstream ss;

                        ss << "cd Calibration && ./Calibration 1 " << idCamera << " " << BROWN << " &";
                        system(ss.str().c_str());
                    }
                }
                if (ImGui::MenuItem("Rotação")){
                    if(useCamera == 0){
                        stringstream ss;

                        ss << "cd Calibration && ./Calibration 0 " << "../" << pathImage << " " << ROTATION << " &";
                        system(ss.str().c_str());
                    }else{
                        stringstream ss;

                        ss << "cd Calibration && ./Calibration 1 " << idCamera << " " << ROTATION << " &";
                        system(ss.str().c_str());
                    }
                }
                if (ImGui::MenuItem("Corte")){
                    if(useCamera == 0){
                        stringstream ss;

                        ss << "cd Calibration && ./Calibration 0 " << "../" << pathImage << " " << CUT << " &";
                        system(ss.str().c_str());
                    }
                    else{
                        stringstream ss;

                        ss << "cd Calibration && ./Calibration 1 " << idCamera << " " << CUT << " &";
                        system(ss.str().c_str());
                    }
                }
                ImGui::EndMenu();
            }

            ImGui::EndMenu();
        }
        
        if (ImGui::BeginMenu("Configurações")){
            if(ImGui::BeginMenu("CameraGL")){
                if(ImGui::MenuItem("Topo")){
                    draw.setCamera(TOP);
                }
                if(ImGui::MenuItem("TV1")){
                    draw.setCamera(TV1);
                }
                ImGui::EndMenu();
            }

            if(report){
                if (ImGui::MenuItem("Relatório", "ON")) {
                    report = false;
                }
            }else{
                if (ImGui::MenuItem("Relatório", "OFF")) {
                    report = true;
                } 
            }

            if(ImGui::MenuItem("Créditos")){
                show_credits_window = !show_credits_window;  
            }

            ImGui::EndMenu();
        }

        if (ImGui::Button("Status")){
            show_status_window = !show_status_window;
        }

        ImGui::EndMainMenuBar();
    }
}

// Tela de Jogo, Ainda não pronta (Johnathan)
void GUI::guiWindowPlay(){
    ImGui::Begin("Tela de Jogo", &show_window_play, ImVec2(200, 150), 0.65, ImGuiWindowFlags_NoResize);
    if(ImGui::Button("Jogar")){

    }
    if(ImGui::Button("Pausar")){

    }
    if(ImGui::Button("Trocar Campo")){
        timePlay = !timePlay;
        draw.setTimePlay(timePlay);
    }
    if(ImGui::Button("Finalizar")){
        core.finishVSS();
        show_window_play = !show_window_play;
    }
    ImGui::End();
}

void GUI::guiWindowCredits(){
    ImGui::Begin("Créditos", &show_credits_window, ImVec2(450, 300), 0.65, ImGuiWindowFlags_NoResize);

    ImGui::TextWrapped("2013");
    ImGui::Spacing();

    ImGui::BulletText("Johnathan Fercher da Rosa (VSS-C)");
    ImGui::BulletText("Oscar Neiva Eulálio Neto (VSS)");
    ImGui::BulletText("Lucas Marques Moreira (VSS)");

    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::TextWrapped("2014");
    ImGui::Spacing();

    ImGui::BulletText("Johnathan Fercher da Rosa (VSS-C)");
    ImGui::BulletText("Oscar Neiva Eulálio Neto (VSS)");
    ImGui::BulletText("Lucas Borsatto Simão (VSS)");
    ImGui::BulletText("Hebert Luiz Cabral da Silva (VSS)");
    
    ImGui::BulletText("Lucas Marques Moreira (2D-C)");
    ImGui::BulletText("Marlon Ferreira (2D)");

    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::TextWrapped("2015");
    ImGui::Spacing();

    ImGui::BulletText("Oscar Neiva Eulálio Neto (VSS-C)");
    ImGui::BulletText("Lucas Borsatto Simão (VSS)");
    ImGui::BulletText("Hebert Luiz Cabral da Silva (VSS)");
    ImGui::BulletText("Johnathan Fercher da Rosa (VSS)");
    ImGui::BulletText("Manoel Stilpen (VSS)");
    ImGui::BulletText("Alexandre S Thiago (VSS)");
    ImGui::BulletText("Felipe Amaral (VSS)");
    ImGui::BulletText("Samantha Vilaça (VSS)");

    ImGui::BulletText("Marlon Ferreira (2D-C)");
    ImGui::BulletText("Pedro Sol (2D)");

    ImGui::End();
}

// Tela de Warnings (Johnathan)
void GUI::guiWindowWarning(){
    ImGui::Begin("Warnings", &show_warning_window, ImVec2(450, 300), 0.65, ImGuiWindowFlags_NoResize);

    ImGui::TextWrapped("Os seguintes problemas foram encontrados:");
    ImGui::Spacing();
    ImGui::Spacing();

    for(int i = 0 ; i < errors.size() ; i++){
        ImGui::BulletText(errors.at(i).c_str());
    }

    ImGui::Spacing();
    ImGui::Spacing();

    if(ImGui::Button("Verificar")){
        checkThings();
    }

    ImGui::End();
}

void GUI::guiWindowStatus(){
   ImGui::Begin("Status", &show_status_window, ImVec2(580, 350), 0.65, ImGuiWindowFlags_NoResize);

    ImGui::TextWrapped("Equipe 1");
    ImGui::Spacing();;

    ImGui::Columns(5, "mycolumns");
    ImGui::Separator();
    ImGui::Text("SIR Robô");    ImGui::NextColumn();
    ImGui::Text("Posição");     ImGui::NextColumn();
    ImGui::Text("Orientação");  ImGui::NextColumn();
    ImGui::Text("Vel .L");      ImGui::NextColumn();
    ImGui::Text("Vel .A");      ImGui::NextColumn();
    ImGui::Separator();

    for(int i = 0 ; i < 3 ; i++){
        stringstream ss;
        ss << robot.at(i).getId();
        ImGui::Text(ss.str().c_str());              ImGui::NextColumn();

        clearSS(ss);
        ss << "(" << robot.at(i).getPosition().x << ", " << robot.at(i).getPosition().y << ")";
        ImGui::Text(ss.str().c_str());              ImGui::NextColumn();
        
        clearSS(ss);
        ss << robot.at(i).getOrientation().y << "°";
        ImGui::Text(ss.str().c_str());              ImGui::NextColumn();

        clearSS(ss);
        ss << "(" << robot.at(i).getLinearVelocity().x << ", " << robot.at(i).getLinearVelocity().y << ")";
        ImGui::Text(ss.str().c_str());              ImGui::NextColumn();

        clearSS(ss);
        ss << robot.at(i).getOrientation().y << "°";
        ImGui::Text(ss.str().c_str());              ImGui::NextColumn();
    }


    ImGui::Columns(1);

    ImGui::Separator();
    ImGui::Spacing();

    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::TextWrapped("Equipe 2");
    ImGui::Spacing();

    ImGui::Columns(5, "mycolumns");
    ImGui::Separator();
    ImGui::Text("ADV Robô");    ImGui::NextColumn();
    ImGui::Text("Posição");     ImGui::NextColumn();
    ImGui::Text("Orientação");  ImGui::NextColumn();
    ImGui::Text("Vel .L");      ImGui::NextColumn();
    ImGui::Text("Vel .A");      ImGui::NextColumn();    
    ImGui::Separator();


    for(int i = 3 ; i < 6 ; i++){
        stringstream ss;
        ss << robot.at(i).getId();
        ImGui::Text(ss.str().c_str());              ImGui::NextColumn();

        clearSS(ss);
        ss << "(" << robot.at(i).getPosition().x << ", " << robot.at(i).getPosition().y << ")";
        ImGui::Text(ss.str().c_str());              ImGui::NextColumn();
        
        clearSS(ss);
        ss << robot.at(i).getOrientation().y << "°";
        ImGui::Text(ss.str().c_str());              ImGui::NextColumn();

        clearSS(ss);
        ss << "(" << robot.at(i).getLinearVelocity().x << ", " << robot.at(i).getLinearVelocity().y << ")";
        ImGui::Text(ss.str().c_str());              ImGui::NextColumn();

        clearSS(ss);
        ss << robot.at(i).getOrientation().y << "°";
        ImGui::Text(ss.str().c_str());              ImGui::NextColumn();
    }

    ImGui::Columns(1);

    ImGui::Separator();
    ImGui::Spacing();

    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::TextWrapped("Processos");
    ImGui::Spacing();

    ImGui::Columns(4, "mycolumns");
    ImGui::Separator();
    ImGui::Text("GUI");                 ImGui::NextColumn();
    ImGui::Text("Core");                ImGui::NextColumn();
    ImGui::Text("Strategy");              ImGui::NextColumn();
    ImGui::Text("Vision");              ImGui::NextColumn();
    ImGui::Separator();

    ImGui::Text("Rodando");              ImGui::NextColumn();
    ImGui::Text("Rodando");              ImGui::NextColumn();

    switch(core.getStrategyStatus()){
        case STOPPED:{ ImGui::Text("Parado");  ImGui::NextColumn(); }  break;
        case STARTING:{ ImGui::Text("Iniciando");  ImGui::NextColumn(); }  break;
        case RUNNING:{ ImGui::Text("Rodando");  ImGui::NextColumn(); }  break;
        case PAUSING:{ ImGui::Text("Pausando");  ImGui::NextColumn(); }  break;
        case PAUSED:{ ImGui::Text("Pausado");  ImGui::NextColumn(); }  break;
        case ENDING:{ ImGui::Text("Finalizando");  ImGui::NextColumn(); }  break;
        case FINISHED:{ ImGui::Text("Finalizado");  ImGui::NextColumn(); }  break;
        case CRASHED:{ ImGui::Text("Quebrado");  ImGui::NextColumn(); }  break;
    }

    switch(core.getVisionStatus()){
        case STOPPED:{ ImGui::Text("Parado");  ImGui::NextColumn(); }  break;
        case STARTING:{ ImGui::Text("Iniciando");  ImGui::NextColumn(); }  break;
        case RUNNING:{ ImGui::Text("Rodando");  ImGui::NextColumn(); }  break;
        case PAUSING:{ ImGui::Text("Pausando");  ImGui::NextColumn(); }  break;
        case PAUSED:{ ImGui::Text("Pausado");  ImGui::NextColumn(); }  break;
        case ENDING:{ ImGui::Text("Finalizando");  ImGui::NextColumn(); }  break;
        case FINISHED:{ ImGui::Text("Finalizado");  ImGui::NextColumn(); }  break;
        case CRASHED:{ ImGui::Text("Quebrado");  ImGui::NextColumn(); }  break;
    }

    ImGui::Columns(1);

    ImGui::Separator();
    ImGui::Spacing();
    ImGui::End();
}

void GUI::guiWindowConfigTeam(int team){
    setCalibrationPosition = true;

    switch(team){
        case OUR_TEAM:{
            static int robotHelper[3] = {0, 0, 0};
            static int taskHelper[3] = {0, 0, 0};
            static int team1 = 0;
            static int strategy = 0;
            static int control = 0;
            static int transmission = 0;

            for(int i = 0 ; i < 3 ; i++){
               robot.at(i).setPosition(btVector3(robot.at(i).getPosition().x, robot.at(i).getPosition().y, 10)); 
               robot.at(i).setOrientation(btVector3(robot.at(i).getOrientation().x, robot.at(i).getOrientation().y+1, robot.at(i).getOrientation().z));
            }
            for(int i = 3 ; i < 6 ; i++){
               robot.at(i).setPosition(btVector3(robot.at(i).getPosition().x, robot.at(i).getPosition().y, -10)); 
            }

            ImGui::Begin("SIR Team", &show_configteam_window, ImVec2(500, 270), 0.65, ImGuiWindowFlags_NoResize);

            ImGui::Text("Configurações do nosso time:");
            ImGui::Spacing();
            ImGui::Spacing();
            ImGui::Combo("Cor do Time", &team1, "Azul\0Amarelo\0\0"); ImGui::NextColumn();

            ImGui::Columns(3, "mixed");
            ImGui::Separator();

            for(int i = 0 ; i < 3 ; i++){
                stringstream ss;
                ss << "Robô " << i+1;
                ImGui::Text(ss.str().c_str()); ImGui::NextColumn();
            }

            for(int i = 0 ; i < 3 ; i++){
                stringstream ss;
                ss << "Cor " << i+1;
                ImGui::Combo(ss.str().c_str(), &robotHelper[i], "Vermelho\0Verde\0Roxo\0Rosa\0Marrom\0\0"); ImGui::NextColumn();
            }

            ImGui::Columns(1);
            ImGui::Spacing();
            ImGui::Spacing();

            ImGui::Separator();
            static char buf1[64] = ""; ImGui::InputText("Nome da Configuração", buf1, 64);

            teamSirOk = 1;
            if (ImGui::Button("Salvar")){
                string s;
                
                for(int i = 0 ; i < 64 ; i++){
                    // Vazio = 0 NESSE CASO
                    if(buf1[i] != 0){
                        s += buf1[i];
                    }
                }

                //cout << s << endl;

                if(s != ""){
                    TeamConfiguration config;
                    stringstream ss;
                    ss << "Data/Teams/" << s << ".csv";

                    config.name = s;

                    // TODO: configurar estratégia, transmissão e controle
                    config.strategy = strategy;
                    config.transmission = transmission;
                    config.control = control;

                    if(team1 == 0)
                        config.teamColor = BLUE;
                    else
                        config.teamColor = YELLOW;

                    // TODO: Escolher a ID dos devidos robôs
                    for(int i = 0 ; i < 3 ; i++){
                        config.id[i] = i;
                        config.task[i] = taskHelper[i];
                        switch(robotHelper[i]){
                            case 0:{
                                config.color[i] = RED;
                            }break;
                            case 1:{
                                config.color[i] = GREEN;
                            }break;
                            case 2:{
                                config.color[i] = PURPLE;
                            }break;
                            case 3:{
                                config.color[i] = PINK;
                            }break;
                            case 4:{
                                config.color[i] = BROWN;
                            }break;
                        }
                    }

                    //config.show();
                    crud.saveTeamConfiguration(ss.str(), config);
                    show_configteam_window = false;
                }
            }

            ImGui::End();

            for(int i = 0 ; i < 3 ; i++){
                if(team1 == 0){
                    robot.at(i).setColorTeam(colors.at(BLUE));
                    robot.at(i).setVisionColorTeam(visionColors.at(BLUE));
                    robot.at(i).setIdColorTeam(BLUE);

                    
                    draw.setColorGoal(0, colors.at(BLUE));
                }else{
                    robot.at(i).setColorTeam(colors.at(YELLOW));
                    robot.at(i).setVisionColorTeam(visionColors.at(YELLOW));
                    robot.at(i).setIdColorTeam(YELLOW);

                    draw.setColorGoal(0, colors.at(YELLOW));
                }          
            }

            for(int i = 0 ; i < 3 ; i++){
                switch(robotHelper[i]){
                    case 0:{
                        robot.at(i).setColorRobot(colors.at(RED));
                        robot.at(i).setVisionColorRobot(visionColors.at(RED));
                        robot.at(i).setIdColorRobot(RED);
                    }break;
                    case 1:{
                        robot.at(i).setColorRobot(colors.at(GREEN));
                        robot.at(i).setVisionColorRobot(visionColors.at(GREEN));
                        robot.at(i).setIdColorRobot(GREEN);
                    }break;
                    case 2:{
                        robot.at(i).setColorRobot(colors.at(PURPLE));
                        robot.at(i).setVisionColorRobot(visionColors.at(PURPLE));
                        robot.at(i).setIdColorRobot(PURPLE);
                    }break;
                    case 3:{
                        robot.at(i).setColorRobot(colors.at(PINK));
                        robot.at(i).setVisionColorRobot(visionColors.at(PINK));
                        robot.at(i).setIdColorRobot(PINK);
                    }break;
                    case 4:{
                        robot.at(i).setColorRobot(colors.at(BROWN));
                        robot.at(i).setVisionColorRobot(visionColors.at(BROWN));
                        robot.at(i).setIdColorRobot(BROWN);
                    }break;
                }
            }
        }break;
        case ADVERSARY_TEAM:{
            static int robotHelper[3] = {0, 0, 0};
            static int taskHelper[3] = {6, 6, 6};
            static int team1 = 0;
            static int strategy = 0;
            static int control = 0;
            static int transmission = 0;

            for(int i = 3 ; i < 6 ; i++){
               robot.at(i).setPosition(btVector3(robot.at(i).getPosition().x, robot.at(i).getPosition().y, 10)); 
               robot.at(i).setOrientation(btVector3(robot.at(i).getOrientation().x, robot.at(i).getOrientation().y+1, robot.at(i).getOrientation().z));
            }
            for(int i = 0 ; i < 3 ; i++){
               robot.at(i).setPosition(btVector3(robot.at(i).getPosition().x, robot.at(i).getPosition().y, -10)); 
            }

            ImGui::Begin("ADV Team", &show_configteam_window, ImVec2(500, 270), 0.65, ImGuiWindowFlags_NoResize);

            ImGui::Text("Configurações do nosso time:");
            ImGui::Spacing();
            ImGui::Spacing();
            ImGui::Combo("Cor do Time", &team1, "Azul\0Amarelo\0\0"); ImGui::NextColumn();

            ImGui::Columns(3, "mixed");
            ImGui::Separator();

            for(int i = 0 ; i < 3 ; i++){
                stringstream ss;
                ss << "Robô " << i+1;
                ImGui::Text(ss.str().c_str()); ImGui::NextColumn();
            }

            for(int i = 0 ; i < 3 ; i++){
                stringstream ss;
                ss << "Cor " << i+1;
                ImGui::Combo(ss.str().c_str(), &robotHelper[i], "Vermelho\0Verde\0Roxo\0Rosa\0Marrom\0\0"); ImGui::NextColumn();
            }

            ImGui::Separator();

            ImGui::Columns(1);
            ImGui::Spacing();
            ImGui::Spacing();
            static char buf1[64] = ""; ImGui::InputText("Nome da Configuração", buf1, 64);

            teamAdvOk = 1;
            if (ImGui::Button("Salvar")){
                string s;
                
                for(int i = 0 ; i < 64 ; i++){
                    // Vazio = 0 NESSE CASO
                    if(buf1[i] != 0){
                        s += buf1[i];
                    }
                }

                //cout << s << endl;

                if(s != ""){
                    TeamConfiguration config;
                    stringstream ss;
                    ss << "Data/Teams/" << s << ".csv";

                    config.name = s;

                    // TODO: configurar estratégia, transmissão e controle
                    config.strategy = strategy;
                    config.transmission = transmission;
                    config.control = control;

                    if(team1 == 0)
                        config.teamColor = BLUE;
                    else
                        config.teamColor = YELLOW;

                    // TODO: Escolher a ID dos devidos robôs
                    for(int i = 0 ; i < 3 ; i++){
                        config.id[i] = i;
                        config.task[i] = taskHelper[i];
                        switch(robotHelper[i]){
                            case 0:{
                                config.color[i] = RED;
                            }break;
                            case 1:{
                                config.color[i] = GREEN;
                            }break;
                            case 2:{
                                config.color[i] = PURPLE;
                            }break;
                            case 3:{
                                config.color[i] = PINK;
                            }break;
                            case 4:{
                                config.color[i] = BROWN;
                            }break;
                        }
                    }

                    //config.show();
                    crud.saveTeamConfiguration(ss.str(), config);
                    show_configteam_window = false;
                }
            }
            
            ImGui::End();

            for(int i = 3 ; i < 6 ; i++){
                if(team1 == 0){
                    robot.at(i).setColorTeam(colors.at(BLUE));
                    robot.at(i).setVisionColorTeam(visionColors.at(BLUE));
                    robot.at(i).setIdColorTeam(BLUE);

                    draw.setColorGoal(1, colors.at(BLUE));
                }else{
                    robot.at(i).setColorTeam(colors.at(YELLOW));
                    robot.at(i).setVisionColorTeam(visionColors.at(YELLOW));
                    robot.at(i).setIdColorTeam(YELLOW);

                    draw.setColorGoal(1, colors.at(YELLOW));
                }           
            }

            for(int i = 0 ; i < 3 ; i++){
                switch(robotHelper[i]){
                    case 0:{
                        robot.at(i+3).setColorRobot(colors.at(RED));
                        robot.at(i+3).setVisionColorRobot(visionColors.at(RED));
                        robot.at(i+3).setIdColorRobot(RED);
                    }break;
                    case 1:{
                        robot.at(i+3).setColorRobot(colors.at(GREEN));
                        robot.at(i+3).setVisionColorRobot(visionColors.at(GREEN));
                        robot.at(i+3).setIdColorRobot(GREEN);
                    }break;
                    case 2:{
                        robot.at(i+3).setColorRobot(colors.at(PURPLE));
                        robot.at(i+3).setVisionColorRobot(visionColors.at(PURPLE));
                        robot.at(i+3).setIdColorRobot(PURPLE);
                    }break;
                    case 3:{
                        robot.at(i+3).setColorRobot(colors.at(PINK));
                        robot.at(i+3).setVisionColorRobot(visionColors.at(PINK));
                        robot.at(i+3).setIdColorRobot(PINK);
                    }break;
                    case 4:{
                        robot.at(i+3).setColorRobot(colors.at(BROWN));
                        robot.at(i+3).setVisionColorRobot(visionColors.at(BROWN));
                        robot.at(i+3).setIdColorRobot(BROWN);
                    }break;
                }
            }
        }break;
        default:{
            cout << "Opcao Invalida !" << endl;
        }break;
    }  
}

void GUI::release(){
    ImGui_ImplGlfw_Shutdown();
    glfwTerminate();
}

void GUI::loop(){
    while (!glfwWindowShouldClose(window))
    {
        ImGui_ImplGlfw_NewFrame();

        guiMainMenu();
        guiShowWindows();

        glfwGetWindowSize(window, &width, &height);
        glViewport(0, 0, width, height);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        gluPerspective(60, (double)width / (double)height, 0.1, 3000);

        glMatrixMode(GL_MODELVIEW);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        draw.drawWorld(robot, ball.getPosition());
        
        ImGui::Render();

        glfwSwapBuffers(window);
        glfwPollEvents();
        usleep(33333);
    }
}

void GUI::guiShowWindows(){
    if(show_window_play){
        guiWindowPlay();
    }

    if(show_test_window){
        ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
        ImGui::ShowTestWindow(&show_test_window);
    }

    if(show_warning_window){
        guiWindowWarning();
    }

    if(show_configteam_window){
        guiWindowConfigTeam(teamSelected);
    }else{
        if(setCalibrationPosition){
            setRobotsDefaultPosition();
            setCalibrationPosition = false;
        }
    }

    if(show_status_window){
        guiWindowStatus();
    }

    if(show_credits_window){
        guiWindowCredits();
    }
}


void GUI::getAllDevices(){
    devices.clear();

    string response = cmdTerminal("find /dev/ -name video*");
    string sp = "";
    for(int i = 0 ; i < response.size() ; i++){
        if(response[i] == '\n'){
            stringstream sap;
            sap << response[i-1];
            devices.push_back(sp);
            sp = ""; 
        }else{
            sp += response[i];
        }
    }

    vector<string> resp;
    for(int i = devices.size()-1 ; i >= 0 ; i--){
        resp.push_back(devices.at(i));
    }

    devices = resp;

    /*for(int i = 0 ; i < devices.size() ; i++){
        cout << devices.at(i) << endl;
    }*/
}


void GUI::getAllImages(){
    images.clear();

    string response = cmdTerminal("find Utils/Images/ -name *jpg");
    string sp = "";
    for(int i = 0 ; i < response.size() ; i++){
        if(response[i] == '\n'){
            images.push_back(sp);
            sp = ""; 
        }else{
            sp += response[i];
        }
    }
}

void GUI::setWindowName(string name){
    this->name = name;
}
void GUI::setWidth(int width){
    this-> width = width;
}
void GUI::setHeight(int height){
    this->height = height;
}

string GUI::getWindowName(){
    return name;
}
int GUI::getWidth(){
    return width;
}
int GUI::getHeight(){
    return height;
}
