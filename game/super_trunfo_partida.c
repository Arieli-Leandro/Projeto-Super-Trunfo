#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include <stdbool.h>
#include "Biblioteca_auxiliar.h"
#include "STlogica.h"
#include "Assetsloader.h"


typedef enum Gamescreen
{
    LOADING,
    GAME,
    MENU_PAUSE,
    GAME_OVER
} Gamescreen; //=---- Estados da Tela
typedef enum Estado_global
{
    IDLE,
    PICKING_UP,
    IDLE_WITH_CARD,
    PROCESSAR_RODADA
} Estado_global; //=---- Estados do bot

#define MJOGADORES 2
#define TARGET_FPS 60




int main(int argc, char **argv)
{
    if (argc != 3)
    {
        printf("=-abra pelo gerenciador ou inclua os argumentos: ./undertale_supertrunfo nome dificuldadeDoBot");
        return 1;
    }
    // dimensões da tela =---------
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    // Escala para as imagens =----------
    const int scale = 12;
    const int scale_cards = 6;

    CartaId *cartas = NULL;

    Jogador jogadores[MJOGADORES];
    strcpy(jogadores[0].nome, argv[1]); // Copiando a string
    jogadores[0].cartasRestantes = 0;
    jogadores[0].mao = NULL;
    jogadores[0].bot = 0;

    strcpy(jogadores[1].nome, "CPU");
    jogadores[1].cartasRestantes = 0; // Se argv[1] for um número, converta corretamente
    jogadores[1].mao = NULL;
    jogadores[1].bot = atoi(argv[2]);
    int totalCartas = 0;
    int numJogadores = 2;

    cartas = carregarCartas("data/dados_salvos.dat", &totalCartas);
    if (!cartas)
        return 1;



    // =------------------------------= BOTOES DO MENU =---------------------------------=
    // botao retornar =------
    Rectangle botao_return;
    botao_return.width = 640;
    botao_return.height = 100;
    botao_return.x = ((float)screenWidth - (float)botao_return.width) / 2.f;
    botao_return.y = (((float)screenHeight - (float)botao_return.height) / 2.f) - 400;

    // botao efeitos sonoros =---------
    Rectangle botao_sounds_effects;
    botao_sounds_effects.width = 640;
    botao_sounds_effects.height = 100;
    botao_sounds_effects.x = ((float)screenWidth - (float)botao_sounds_effects.width) / 2.f;
    botao_sounds_effects.y = (((float)screenHeight - (float)botao_sounds_effects.height) / 2.f) - 200;
    bool efeitos_sonoros_ligados = false; // verifica se os efeitos sonoros esta ligado ou não
    // Slider dos efeitos sonoros =------
    Rectangle slider_efeitos_sonoros = {botao_sounds_effects.x + 50, botao_sounds_effects.y + 103, 200, 20};

    // botao musica =---------
    Rectangle botao_musica;
    botao_musica.width = 640;
    botao_musica.height = 100;
    botao_musica.x = ((float)screenWidth - (float)botao_musica.width) / 2.f;
    botao_musica.y = (((float)screenHeight - (float)botao_musica.height) / 2.f);
    bool musica_ligada = false; // verifica se a musica esta ligado ou não
    // Slider da musica =------
    Rectangle slider_musica = {botao_musica.x + 50, botao_musica.y + 103, 200, 20};

    // botao sair =----------
    Rectangle botao_sair;
    botao_sair.width = 640;
    botao_sair.height = 100;
    botao_sair.x = ((float)screenWidth - (float)botao_sair.width) / 2.f;
    botao_sair.y = (((float)screenHeight - (float)botao_sair.height) / 2.f) + 200;
    bool desliga = false; // verifica se o botao foi apertado

    // =------------------------------= BOTOES DA TELA DE GAME OVER =---------------------------------=
    // botao sair =----------
    Rectangle botao_sair_game_over;
    botao_sair_game_over.width = 300;
    botao_sair_game_over.height = 100;
    botao_sair_game_over.x = (((float)screenWidth - (float)botao_sair_game_over.width) / 2.f);
    botao_sair_game_over.y = (((float)screenHeight - (float)botao_sair_game_over.height) / 2.f) + 400;

    // botao jogar novamente =----------
    Rectangle botao_jogar_novamente;
    botao_jogar_novamente.width = 500;
    botao_jogar_novamente.height = 100;
    botao_jogar_novamente.x = (((float)screenWidth - (float)botao_jogar_novamente.width) / 2.f);
    botao_jogar_novamente.y = (((float)screenHeight - (float)botao_jogar_novamente.height) / 2.f) + 250;

    // =---------------------------= BOTOES DA CARTA =-----------------------------------=
    // BOTOES DO JOGADOR =-----------------------------------------
    // Botão do Fight =------
    Rectangle botao_fight;
    botao_fight.width = 51 * scale_cards;
    botao_fight.height = 8 * scale_cards;
    botao_fight.x = 160;
    botao_fight.y = 596;

    // Botão do IQ =------
    Rectangle botao_IQ;
    botao_IQ.width = 51 * scale_cards;
    botao_IQ.height = 8 * scale_cards;
    botao_IQ.x = 160;
    botao_IQ.y = 596 + 78;

    // Botão do Danger =------
    Rectangle botao_danger;
    botao_danger.width = 51 * scale_cards;
    botao_danger.height = 8 * scale_cards;
    botao_danger.x = 160;
    botao_danger.y = 596 + 78 * 2;

    // Botão do Mercy =------
    Rectangle botao_mercy;
    botao_mercy.width = 51 * scale_cards;
    botao_mercy.height = 8 * scale_cards;
    botao_mercy.x = 160;
    botao_mercy.y = 596 + 78 * 3;

    // BOTOES DO BOT =-------------------------------------------------
    // Botão do Fight =------
    Rectangle botao_fight_bot;
    botao_fight_bot.width = 51 * scale_cards;
    botao_fight_bot.height = 8 * scale_cards;
    botao_fight_bot.x = 1388;
    botao_fight_bot.y = 596;

    // Botão do IQ =------
    Rectangle botao_IQ_bot;
    botao_IQ_bot.width = 51 * scale_cards;
    botao_IQ_bot.height = 8 * scale_cards;
    botao_IQ_bot.x = 1388;
    botao_IQ_bot.y = 596 + 78;

    // Botão do Danger =------
    Rectangle botao_danger_bot;
    botao_danger_bot.width = 51 * scale_cards;
    botao_danger_bot.height = 8 * scale_cards;
    botao_danger_bot.x = 1388;
    botao_danger_bot.y = 596 + 78 * 2;

    // Botão do Mercy =------
    Rectangle botao_mercy_bot;
    botao_mercy_bot.width = 51 * scale_cards;
    botao_mercy_bot.height = 8 * scale_cards;
    botao_mercy_bot.x = 1388;
    botao_mercy_bot.y = 596 + 78 * 3;

    // =-------------------------------------------------------= INICIALIZANDO A JANELA =-------------------------------------------------------------------------= //
    InitWindow(screenWidth, screenHeight, "UnderTrunfo");
    InitAudioDevice();

    // =------------------------------= MUSICAS E SONS =---------------------------------=
    // Musica do bot =--------
    Music bot_theme = LoadMusicStream("sounds/Toby Fox - Megalovania [Electro Swing Remix].mp3");
    float volume_musica = 0.5f;
    bot_theme.looping = true;

    // som para toda vez que o jogador apertar qualquer botão =--------
    Sound snd_select = LoadSound("sounds/snd_select.wav");
    float volume_sound = 0.5f;

    //=-------------------= DADOS DO BACKGROUND (PARTIDA) =-----------------------------------------------------------=
    Texture2D sprite_background = LoadTexture("img/bg/sprite_background.png"); // nome do arquivo
    // Adicionando a escala certa -----------------=
    sprite_background.width = sprite_background.width * scale;
    sprite_background.height = sprite_background.height * scale;
    // centralizando o background para que ele fique em tela cheia
    int pos_x = ((float)screenWidth / 2) - ((float)sprite_background.width / 2);
    int pos_y = ((float)screenHeight / 2) - ((float)sprite_background.height / 2);

    //=-------------------= DADOS DO BACKGROUND (MENU PAUSE) =-----------------------------------------------------------=
    Texture2D sprite_background_menu = LoadTexture("img/bg/background_menu_pause.png"); // nome do arquivo
    // Adicionando a escala certa -----------------=
    sprite_background_menu.width = sprite_background_menu.width * scale;
    sprite_background_menu.height = sprite_background_menu.height * scale;
    // centralizando o background para que ele fique em tela cheia
    int pos_x_menu = ((float)screenWidth / 2) - ((float)sprite_background_menu.width / 2);
    int pos_y_menu = ((float)screenHeight / 2) - ((float)sprite_background_menu.height / 2);

    //=-------------------= DADOS DO BACKGROUND (GAME OVER / WIN) =-----------------------------------------------------------=
    Texture2D sprite_background_win = LoadTexture("img/bg/sprite_background_win.png");             // nome do arquivo
    Texture2D sprite_background_game_over = LoadTexture("img/bg/sprite_background_game_over.png"); // nome do arquivo

    // Adicionando a escala certa (WIN)-----------------=
    sprite_background_win.width = sprite_background_win.width * scale;
    sprite_background_win.height = sprite_background_win.height * scale;
    // centralizando o background para que ele fique em tela cheia (WIN)
    int pos_x_win = ((float)screenWidth / 2) - ((float)sprite_background_win.width / 2);
    int pos_y_win = ((float)screenHeight / 2) - ((float)sprite_background_win.height / 2);

    // Adicionando a escala certa (GAME OVER)-----------------=
    sprite_background_game_over.width = sprite_background_game_over.width * scale;
    sprite_background_game_over.height = sprite_background_game_over.height * scale;
    // centralizando o background para que ele fique em tela cheia (GAME OVER)
    int pos_x_game_over = ((float)screenWidth / 2) - ((float)sprite_background_game_over.width / 2);
    int pos_y_game_over = ((float)screenHeight / 2) - ((float)sprite_background_game_over.height / 2);

    //=-------------------------------= DADOS DO DECK =---------------------------------------------------------=
    Texture2D sprite_deck = LoadTexture("img/sprite_deck.png");
    // Adicionando a escala certa -----------=
    sprite_deck.width = sprite_deck.width * scale;
    sprite_deck.height = sprite_deck.height * scale;

    //=--------------------= DADOS DO DECK (PICKING_UP) =----------------------------------------------------------=
    Texture2D sprite_deck_picking_up = LoadTexture("img/sprites_sheets/sprite_sheet_deck.png"); // nome do arquivo
    // Adicionando a escala certa -----------=
    sprite_deck_picking_up.width = sprite_deck_picking_up.width * scale;
    sprite_deck_picking_up.height = sprite_deck_picking_up.height * scale;
    Rectangle source_deck = {0.f, 0.f, ((float)sprite_deck_picking_up.width / 4.f), sprite_deck_picking_up.height};

    int frame_deck = 0;            // frames do deck
    float runningtime_deck = 0.0f; // tempo do deck

    //=-------------------------------= DADOS DO CONTADOR DE DECK 1 =---------------------------------------------------------=
    Texture2D sprite_deck_counter = LoadTexture("img/sprite_deck_counter_1.png");
    // Adicionando a escala certa -----------=
    sprite_deck_counter.width = sprite_deck_counter.width * scale;
    sprite_deck_counter.height = sprite_deck_counter.height * scale;

    //=-------------------------------= DADOS DO CONTADOR DE DECK 2 =---------------------------------------------------------=
    Texture2D sprite_deck_counter_2 = LoadTexture("img/sprite_deck_counter.png");
    // Adicionando a escala certa -----------=
    sprite_deck_counter_2.width = sprite_deck_counter_2.width * scale;
    sprite_deck_counter_2.height = sprite_deck_counter_2.height * scale;

    //=-------------------------------= DADOS DAS CARTAS =---------------------------------------------------------=
    Texture2D sprite_modelo_carta = LoadTexture("img/sprite_modelo_carta.png");
    Texture2D sprite_modelo_carta_supertrunfo = LoadTexture("img/sprite_modelo_carta_super_trunfo.png");
    Texture2D sprite_modelo_carta_bloqueado = LoadTexture("img/sprite_modelo_carta_bloqueado.png");
    Texture2D sprite_modelo_carta_supertrunfo_bloqueado = LoadTexture("img/sprite_modelo_carta_super_trunfo_bloqueado.png");
    Texture2D sprite_modelo_carta_bot = LoadTexture("img/sprite_modelo_carta.png");
    // Adicionando a escala certa -----------=
    sprite_modelo_carta.width = sprite_modelo_carta.width * scale_cards;
    sprite_modelo_carta.height = sprite_modelo_carta.height * scale_cards;
    // Adicionando a escala certa (SUPERTRUNFO) -----------=
    sprite_modelo_carta_supertrunfo.width = sprite_modelo_carta_supertrunfo.width * scale_cards;
    sprite_modelo_carta_supertrunfo.height = sprite_modelo_carta_supertrunfo.height * scale_cards;
    // Adicionando a escala certa (BLOQUEADA) ----------=
    sprite_modelo_carta_bloqueado.width = sprite_modelo_carta_bloqueado.width * scale_cards;
    sprite_modelo_carta_bloqueado.height = sprite_modelo_carta_bloqueado.height * scale_cards;
    // Adicionando a escala certa (SUPERTRUNFO BLOQUEADO) -----------=
    sprite_modelo_carta_supertrunfo_bloqueado.width = sprite_modelo_carta_supertrunfo_bloqueado.width * scale_cards;
    sprite_modelo_carta_supertrunfo_bloqueado.height = sprite_modelo_carta_supertrunfo_bloqueado.height * scale_cards;
    // Adicionando a escala certa (BOT) -----------=
    sprite_modelo_carta_bot.width = sprite_modelo_carta_bot.width * scale_cards;
    sprite_modelo_carta_bot.height = sprite_modelo_carta_bot.height * scale_cards;

    //=-------------------------------= DADOS DO VALOR ESCOLHIDO JOGADOR (SPRITE) =---------------------------------------------------------=
    Texture2D sprite_valor_escolhido_jogador = LoadTexture("img/sprite_valor_escolhido_jogador.png");
    // Adicionando a escala certa -----------=
    sprite_valor_escolhido_jogador.width = sprite_valor_escolhido_jogador.width * scale;
    sprite_valor_escolhido_jogador.height = sprite_valor_escolhido_jogador.height * scale;

    //=-------------------------------= DADOS DO VALOR ESCOLHIDO BOT(SPRITE) =---------------------------------------------------------=
    Texture2D sprite_valor_escolhido_bot = LoadTexture("img/sprite_valor_escolhido_bot.png");
    // Adicionando a escala certa -----------=
    sprite_valor_escolhido_bot.width = sprite_valor_escolhido_bot.width * scale;
    sprite_valor_escolhido_bot.height = sprite_valor_escolhido_bot.height * scale;

    //=--------------------= DADOS DO BOT (IDLE) =----------------------------------------------------------=
    Texture2D sprite_bot_idle = LoadTexture("img/sprites_sheets/sprite_sheet_chara_idle.png"); // nome do arquivo (idle)
    // Adicionando a escala certa -----------=
    sprite_bot_idle.width = sprite_bot_idle.width * scale;
    sprite_bot_idle.height = sprite_bot_idle.height * scale;
    Rectangle source_idle = {0.f, 0.f, ((float)sprite_bot_idle.width / 4.f), sprite_bot_idle.height};

    int frame_idle = 0;            // frames do bot
    float runningtime_idle = 0.0f; // tempo do bot

    //=--------------------= DADOS DO BOT (PICKING_UP) =-------------------------------------------------------------=
    Texture2D sprite_bot_picking_up = LoadTexture("img/sprites_sheets/sprite_sheet_chara_picking_card.png"); // nome do arquivo (picking up)
    // Adicionando a escala certa ----------=
    sprite_bot_picking_up.width = sprite_bot_picking_up.width * scale;
    sprite_bot_picking_up.height = sprite_bot_picking_up.height * scale;
    Rectangle source_picking_up = {0.f, 0.f, ((float)sprite_bot_picking_up.width / 4.f), sprite_bot_picking_up.height};

    int frame_picking_up = 0;            // frames do bot
    float runningtime_picking_up = 0.0f; // tempo do bot

    //=--------------------= DADOS DO BOT (IDLE_WITH_CARD) =-------------------------------------------------------------=
    Texture2D sprite_bot_idle_with_card = LoadTexture("img/sprites_sheets/sprite_sheet_chara_idle_with_card.png"); // nome do arquivo (idle with card)
    // Adicionando a escala certa -----------=
    sprite_bot_idle_with_card.width = sprite_bot_idle_with_card.width * scale;
    sprite_bot_idle_with_card.height = sprite_bot_idle_with_card.height * scale;
    Rectangle source_idle_with_card = {0.f, 0.f, ((float)sprite_bot_idle_with_card.width / 4.f), sprite_bot_idle_with_card.height};

    int frame_idle_with_card = 0;            // frames do bot
    float runningtime_idle_with_card = 0.0f; // tempo do bot

    // =----- POSIÇÃO DO BOT ----------------------------------------------------------------------------------= //
    // Posicionamento do bot
    int pos_x_bot = (screenWidth / 2) - 492;
    int pos_y_bot = (screenHeight / 2) - 408;

    Vector2 position_bot = {pos_x_bot, pos_y_bot};

    // =----- POSIÇÃO DO DECK ---------------------------------------------------------------------------------= //
    // Posicionamento do deck
    int pos_x_deck = ((float)screenWidth / 2.f) + 480;
    int pos_y_deck = ((float)screenHeight / 2.f) + 130;

    Vector2 position_deck = {pos_x_deck, pos_y_deck};

    // =----- POSIÇÃO DO CONTADOR DE DECK 1 ---------------------------------------------------------------------------------= //
    // Posicionamento do deck
    int pos_x_deck_counter = ((float)screenWidth / 2.f) - 240;
    int pos_y_deck_counter = ((float)screenHeight / 2.f) + 200;

    Vector2 position_deck_counter = {pos_x_deck_counter, pos_y_deck_counter};

    // =----- POSIÇÃO DO CONTADOR DE DECK 2 ---------------------------------------------------------------------------------= //
    // Posicionamento do deck
    int pos_x_deck_counter_2 = ((float)screenWidth / 2.f) - 240;
    int pos_y_deck_counter_2 = ((float)screenHeight / 2.f) - 612;

    Vector2 position_deck_counter_2 = {pos_x_deck_counter_2, pos_y_deck_counter_2};

    // =----- POSIÇÃO DA CARTA ---------------------------------------------------------------------------------= //
    // Posicionamento da carta (jogador)
    int pos_x_carta = 100;
    int pos_y_carta = 200;

    int pos_y_carta_adicional = 1000;

    Vector2 position_carta;
    position_carta.x = pos_x_carta;
    position_carta.y = pos_y_carta + pos_y_carta_adicional;

    // Posicionamento da carta (bot)
    int pos_x_carta_bot = screenWidth - sprite_modelo_carta_bot.width - 100;
    int pos_y_carta_bot = 200;

    int pos_y_carta_adicional_bot = 1000;

    Vector2 position_carta_bot;
    position_carta_bot.x = pos_x_carta_bot;
    position_carta_bot.y = pos_y_carta_bot - pos_y_carta_adicional_bot;

    // =----- POSIÇÃO DA CAIXA DE VALOR DO ATRIBUTO ESCOLHIDO ---------------------------------------------------------------------------------= //
    int pos_x_valor_jogador = ((float)sprite_modelo_carta.width / 2.f) - 140;
    int pos_y_valor_jogador = pos_y_carta - 300;

    Vector2 position_valor_jogador = {pos_x_valor_jogador, pos_y_valor_jogador};

    // =----- POSIÇÃO DA CAIXA DE VALOR DO ATRIBUTO ESCOLHIDO (BOT) ---------------------------------------------------------------------------------= //
    int pos_x_valor_bot = (pos_x_carta_bot + ((float)sprite_modelo_carta_bot.width / 2.f) - 240);
    int pos_y_valor_bot = pos_y_carta_bot - 300;

    Vector2 position_valor_bot = {pos_x_valor_bot, pos_y_valor_bot};


    // =--------------------------------------------------------------------------------------------------------= //

    SetTargetFPS(60);                     // SETANDO O FPS =---------------------------------=
    const float updatetime_rapido = 0.1f; // TEMPO ACELERADO -------------=
    const float updatetime = 0.2f;        // TEMPO GLOBAL -----------------------=

    Estado_global estado_global = IDLE; // Inicializando o bot como "IDLE"
    Gamescreen tela_jogo = LOADING;     // Inicializando a tela como "LOADING"
                                        // =--------------------------------------------------------------------------------------------------------= //
    // Tela de loading
    Texture2D sprite_loading_background = LoadTexture("img/bg/loading_background.png");
    sprite_loading_background.width = screenWidth - 85;
    sprite_loading_background.height = screenHeight - 85;

    int pos_x_loading = ((float)screenWidth / 2) - ((float)sprite_loading_background.width / 2);
    int pos_y_loading = ((float)screenHeight / 2) - ((float)sprite_loading_background.height / 2.09);

    // config loading =-----------------------------------------------=

    int numProgresso = 0;

    // asstes loader



    // imagem das cartas
    char caminho_per[] = "img/per/";
    char **nomes_sprites = scan_assets(caminho_per, totalCartas+5);
    char nome_carta[41];

    char sprites_per_buffer[100];
    Texture2D sprites_per[totalCartas+5];


    for (int i = 0; nomes_sprites[i] != NULL; i++)
    {
        strcpy(sprites_per_buffer,  caminho_per);
        strcat(sprites_per_buffer, nomes_sprites[i]);
        sprites_per[i] = LoadTexture(sprites_per_buffer);


        sprites_per[i].width = sprites_per[i].width * scale_cards;
        sprites_per[i].height = sprites_per[i].height * scale_cards;
    }

    // Carta padrao
    int sprite_per_padrao;

    for (int i = 0; nomes_sprites[i] != NULL; i++)
    {
        if (strstr(nomes_sprites[i], "padrao") != NULL)
        {
            sprite_per_padrao = i;
            break;
        }
    }

    // =--------------------------------------------------------------------------------------------------------= //

    // VARIAVEIS AUXILIARES =-------------------------------------------------------------------=
    // animacoes de "picking card"
    int animacao_finalizada = 0;

    // variavel que verifica se a posição da carta na tela esta no lugar certo
    bool movimento_finalizado = false;
    bool movimento_finalizado_bot = false;

    // verifica se o jogo foi começado
    bool cartas_distribuidas = false;

    // variaveis que verificam qual é a tela de jogo atual
    bool tela_game = false;      // tela da partida
    bool tela_game_over = false; // tela de vitoria/derrota

    int contador_frames = 0; // framecounter
    bool acao_feita = false;

    // VARIAVEIS AUXILIARES DA PARTE LOGICA =-----------
    int valor_teclado = -1;

    int indice_empate = 0;

    int ganhador = -1;

    int JogadorDaVez = 0;

    int resultado_rodada = -1;

    bool embaralhado = false;

    // VARIAVEIS DAS CARTAS =---------
    //atributos do jogador =-----
    char valor_atributo_fight[5];
    char valor_atributo_iq[5];
    char valor_atributo_danger[5];
    char valor_atributo_mercy[5];

    //atributos do bot =-----
    char valor_atributo_fight_bot[5];
    char valor_atributo_iq_bot[5];
    char valor_atributo_danger_bot[5];
    char valor_atributo_mercy_bot[5];

    // numero de cartas de cada jogador
    char numero_de_cartas_p1[4];
    char numero_de_cartas_p2[4];

    // Vetor dos atributos
    char atributos[4][10] = {"FIGHT/", "IQ/", "DANGER/", "MERCY/"};

    // =-----------------------------------------------------------------------=

    while (!WindowShouldClose())
    {
        // Verificando se a tela esta cheia =-----------------=
        if (IsKeyPressed(KEY_Q))
        {
            if (IsWindowFullscreen() == false)
            {
                ToggleFullscreen();
            }
            else
            {
                ToggleFullscreen();
            }
        }

        BeginDrawing(); // BEGIN DRAWING =------------------------------------=
        ClearBackground(BLACK);

        // Verificando se a musica esta ligada ou nao
        if (musica_ligada == true)
        {
            UpdateMusicStream(bot_theme);
        }

        // Verificação para ver se o botão sair for apertado para que o programa desligue
        if (desliga == true)
            break;

        //// =-----------------------------------------------------= SISTEMA DA TELA DE JOGO =------------------------------------------------------------------= ////
        switch (tela_jogo)
        {

        case LOADING:
            if (numProgresso >= (screenWidth / 10) && numProgresso >= totalCartas+6)
            {
                tela_jogo = GAME;
            }

            else
            {

                // inclui o ID de cada sprite na carta Sprites personagens ______________________________________________________________
                if (numProgresso < totalCartas)
                {

                    strcpy(nome_carta, cartas[numProgresso].nome);

                    padronizar_nome(nome_carta);

                    for (int i = 0; nomes_sprites[i] != NULL; i++)
                    {
                       
                        if (strstr(nomes_sprites[i], nome_carta) != NULL)
                        {
                            cartas[numProgresso].imgid = i;
                            
                            break;
                        }
                    }

                    if (cartas[numProgresso].imgid == -1)
                    {
                        cartas[numProgresso].imgid = sprite_per_padrao;
                       
                    }
                }
                numProgresso++;
            }

            DrawTexture(sprite_loading_background, pos_x_loading, pos_y_loading, WHITE);

            for (int i = 0; i < numProgresso; i++)
            {
                DrawRectangle(i * 10, screenHeight - 50, 5, 50, GRAY);
            }

            break;
        case GAME:
            // Garantindo que a tela atual é a tela da partida
            tela_game_over = false;
            tela_game = true;

            DrawTexture(sprite_background, pos_x, pos_y, WHITE); // BACKGROUND =---------------------

            DrawTexture(sprite_deck, position_deck.x, position_deck.y, WHITE);                               // sprite do deck (JOGADOR)
            DrawTexture(sprite_deck_counter, position_deck_counter.x, position_deck_counter.y, WHITE);       // contador de cartas (JOGADOR)
            DrawTexture(sprite_deck_counter_2, position_deck_counter_2.x, position_deck_counter_2.y, WHITE); // contador de cartas (BOT)

            // TECLA PARA PAUSAR O JOGO
            if (IsKeyPressed(KEY_V))
                tela_jogo = MENU_PAUSE;

            // =--------------------------------= SISTEMA DE ESTADOS GLOBAL =---------------------------------------=
            switch (estado_global)
            {
            case IDLE: // PARTE ONDE AS CARTAS SERAO EMBARALHADAS E DISTRIBUIDAS PARA OS JOGADORES (JOGADOR E BOT) =-----------------------

                if (embaralhado == false)
                {
                    embaralharCartas(cartas, totalCartas);
                    if (distribuirCartas(cartas, totalCartas, jogadores, numJogadores))
                    {

                        sprintf(numero_de_cartas_p1, "%d", jogadores[0].cartasRestantes);
                        sprintf(numero_de_cartas_p2, "%d", jogadores[1].cartasRestantes);
                        cartas_distribuidas = true;
                    }
                    embaralhado = true;
                }

                DrawText(numero_de_cartas_p1, ((float)screenWidth / 2.f) - 36, ((float)screenHeight / 2.f) + 370, 90, WHITE);
                DrawText(numero_de_cartas_p2, ((float)screenWidth / 2.f) - 36, ((float)screenHeight / 2.f) - 443, 90, WHITE);

                // reposicionando as cartas para fora da tela
                movimento_finalizado = false;
                movimento_finalizado_bot = false;
                pos_y_carta_adicional = 1000;
                pos_y_carta_adicional_bot = 1000;

                // ANIMAÇÃO DO BOT PARADO
                Animacao(sprite_bot_idle, 4, &frame_idle, &source_idle, position_bot, updatetime, &runningtime_idle);

                if (cartas_distribuidas == true)
                {
                    if (acao_feita == false)
                    {
                        contador_frames++;

                        if (contador_frames >= 5 * TARGET_FPS)
                        { // 5 segundos em 60 FPS
                            acao_feita = true;
                        }
                    }
                    else
                    {
                        estado_global = PICKING_UP;
                    }
                }
            break;

            case PICKING_UP: // PARTE SOMENTE PARA ANIMAÇÃO =---------------------------------------

                //RESET em todas as variaveis--//
                contador_frames = 0;
                acao_feita = false;
                movimento_finalizado = false;
                movimento_finalizado_bot = false;
                pos_y_carta_adicional = 1000;
                pos_y_carta_adicional_bot = 1000;
                // ----------------------------//

                DrawText(numero_de_cartas_p1, ((float)screenWidth / 2.f) - 36, ((float)screenHeight / 2.f) + 370, 90, WHITE);
                DrawText(numero_de_cartas_p2, ((float)screenWidth / 2.f) - 36, ((float)screenHeight / 2.f) - 443, 90, WHITE);

                // ANIMAÇÃO DO BOT PEGANDO A CARTA
                if (Animacao(sprite_bot_picking_up, 4, &frame_picking_up, &source_picking_up, position_bot, updatetime_rapido, &runningtime_picking_up) == true)
                {
                    animacao_finalizada++;
                }
                // ANIMAÇÃO PEGANDO CARTA DO DECK
                if (Animacao(sprite_deck_picking_up, 4, &frame_deck, &source_deck, position_deck, updatetime_rapido, &runningtime_deck) == true)
                {
                    animacao_finalizada++;
                }

                // VERIFICA SE AS ANIMAÇÕES FORAM FEITAS
                if (animacao_finalizada == 2)
                {
                    animacao_finalizada = 0;
                    estado_global = IDLE_WITH_CARD;
                }
            break;

            case PROCESSAR_RODADA:

                DrawText(numero_de_cartas_p1, ((float)screenWidth / 2.f) - 36, ((float)screenHeight / 2.f) + 370, 90, WHITE);
                DrawText(numero_de_cartas_p2, ((float)screenWidth / 2.f) - 36, ((float)screenHeight / 2.f) - 443, 90, WHITE);
                // ANIMAÇÃO DO BOT PARADO COM A CARTA
                Animacao(sprite_bot_idle_with_card, 4, &frame_idle_with_card, &source_idle_with_card, position_bot, updatetime, &runningtime_idle_with_card);

                if (JogadorDaVez == 0)
                {

                    //GARANTIR QUE OS SPRITES NAO DESAPAREÇAM =------------------------------------------------------------------------------------------------------- //
                    // garantindo que a carta do jogador apareça no local certo
                    DrawTexture(sprites_per[jogadores[0].mao[indice_empate].imgid], position_carta.x + (4 * scale_cards), pos_y_carta + (4 * scale_cards), WHITE);
                    if (jogadores[0].mao[indice_empate].superTrunfo)
                    {
                        // modelo da carta super trunfo com opçoes bloqueadas
                        DrawTexture(sprite_modelo_carta_supertrunfo_bloqueado, position_carta.x, pos_y_carta, WHITE);
                    }
                    else
                    {
                        // modelo da carta com opçoes bloqueadas
                        DrawTexture(sprite_modelo_carta_bloqueado, position_carta.x, pos_y_carta, WHITE);
                    }
                    
                    // desenhando botoes falsos
                    Fakebutton(botao_fight, "FIGHT");   // botao fight falso
                    Fakebutton(botao_IQ, "IQ");         // botao iq falso
                    Fakebutton(botao_danger, "DANGER"); // botao danger falso
                    Fakebutton(botao_mercy, "MERCY");   // botao mercy falso
                    // mostrando o nome da carta
                    DrawText(Maiusculo(jogadores[0].mao[indice_empate].nome), (botao_fight.x) + 45, (botao_fight.y) - 70, 32, WHITE);

                    // convertendo os valores da carta para char
                    sprintf(valor_atributo_fight, "%d", jogadores[0].mao[indice_empate].fight);
                    sprintf(valor_atributo_iq, "%d", jogadores[0].mao[indice_empate].iq);
                    sprintf(valor_atributo_danger, "%d", jogadores[0].mao[indice_empate].danger);
                    sprintf(valor_atributo_mercy, "%d", jogadores[0].mao[indice_empate].mercy);

                    DrawText(Maiusculo(valor_atributo_fight), (botao_fight.x) + 325, (botao_fight.y) + 6, 32, WHITE);
                    DrawText(Maiusculo(valor_atributo_iq), (botao_IQ.x) + 325, (botao_IQ.y) + 6, 32, WHITE);
                    DrawText(Maiusculo(valor_atributo_danger), (botao_danger.x) + 325, (botao_danger.y) + 6, 32, WHITE);
                    DrawText(Maiusculo(valor_atributo_mercy), (botao_mercy.x) + 325, (botao_mercy.y) + 6, 32, WHITE);

                    DrawText(TextFormat("%c", jogadores[0].mao[indice_empate].letraClassificacao), (pos_x_carta) + 48, (pos_y_carta) + 30, 48, WHITE);
                    DrawText(TextFormat("%d", jogadores[0].mao[indice_empate].numeroClassificacao), (pos_x_carta) + 20, (pos_y_carta) + 30, 48, WHITE);
                    // ------------------------------------------------------------------------------------------------------------------------------------------ //
                    
                    if (movimento_finalizado_bot == false)
                    {
                        DrawTexture(sprite_modelo_carta_bot, position_carta_bot.x, pos_y_carta_bot - pos_y_carta_adicional_bot, WHITE);
                        if (pos_y_carta_adicional_bot >= 0)
                        {
                            pos_y_carta_adicional_bot = pos_y_carta_adicional_bot - 40;
                            if (pos_y_carta_adicional_bot == 0)
                            {
                                movimento_finalizado_bot = true;
                            }
                        }
                    } 
                    else if (movimento_finalizado_bot == true)
                    {
                        // MOSTRANDO OS DADOS DAS CARTAS DO BOT =-------------------------------------------------------------
                        DrawTexture(sprites_per[jogadores[1].mao[indice_empate].imgid], position_carta_bot.x + (4 * scale_cards), pos_y_carta_bot + (4 * scale_cards), WHITE);
                        if (jogadores[1].mao[indice_empate].superTrunfo)
                        {
                            DrawTexture(sprite_modelo_carta_supertrunfo, position_carta_bot.x, pos_y_carta_bot, WHITE);
                        }
                        else
                        {
                            DrawTexture(sprite_modelo_carta_bot, position_carta_bot.x, pos_y_carta_bot, WHITE);
                        }

                        Fakebutton(botao_fight_bot, "FIGHT");   // botao fight falso
                        Fakebutton(botao_IQ_bot, "IQ");         // botao iq falso
                        Fakebutton(botao_danger_bot, "DANGER"); // botao danger falso
                        Fakebutton(botao_mercy_bot, "MERCY");   // botao mercy falso

                        DrawText(Maiusculo(jogadores[1].mao[indice_empate].nome), (botao_fight_bot.x) + 45, (botao_fight_bot.y) - 70, 32, WHITE);

                        // convertendo os valores da carta para char
                        sprintf(valor_atributo_fight_bot, "%d", jogadores[1].mao[indice_empate].fight);
                        sprintf(valor_atributo_iq_bot, "%d", jogadores[1].mao[indice_empate].iq);
                        sprintf(valor_atributo_danger_bot, "%d", jogadores[1].mao[indice_empate].danger);
                        sprintf(valor_atributo_mercy_bot, "%d", jogadores[1].mao[indice_empate].mercy);

                        DrawText(Maiusculo(valor_atributo_fight_bot), (botao_fight_bot.x) + 325, (botao_fight_bot.y) + 6, 32, WHITE);
                        DrawText(Maiusculo(valor_atributo_iq_bot), (botao_IQ_bot.x) + 325, (botao_IQ_bot.y) + 6, 32, WHITE);
                        DrawText(Maiusculo(valor_atributo_danger_bot), (botao_danger_bot.x) + 325, (botao_danger_bot.y) + 6, 32, WHITE);
                        DrawText(Maiusculo(valor_atributo_mercy_bot), (botao_mercy_bot.x) + 325, (botao_mercy_bot.y) + 6, 32, WHITE);

                        DrawText(TextFormat("%c", jogadores[1].mao[indice_empate].letraClassificacao), (pos_x_carta_bot) + 48, (pos_y_carta_bot) + 30, 48, WHITE);
                        DrawText(TextFormat("%d", jogadores[1].mao[indice_empate].numeroClassificacao), (pos_x_carta_bot) + 20, (pos_y_carta_bot) + 30, 48, WHITE);
                        // ----------------------------------------------------------------------------------------------------------------------------------- //

                        if (acao_feita == false)
                        {
                            contador_frames++;
                            if (contador_frames >= 2 * TARGET_FPS)
                            {
                                DrawTexture(sprite_valor_escolhido_jogador, position_valor_jogador.x, position_valor_jogador.y, WHITE);
                                DrawTexture(sprite_valor_escolhido_bot, position_valor_bot.x, position_valor_bot.y, WHITE);

                                //DESENHANDO DO ATRIBUTO ESCOLHIDO E SEU RESPECTIVO VALOR (JOGADOR) =-------------------------------------------------------- 
                                DrawText(atributos[valor_teclado], (position_valor_jogador.x) + 75,(position_valor_jogador.y) + 180, 55, WHITE);
                                if (valor_teclado == 0)
                                {
                                    DrawText(TextFormat("%d", jogadores[0].mao[indice_empate].fight), position_valor_jogador.x + sprite_valor_escolhido_jogador.width - 130, (position_valor_jogador.y) + 194, 40, WHITE);
                                } 
                                else if (valor_teclado == 1)
                                {
                                    DrawText(TextFormat("%d", jogadores[0].mao[indice_empate].iq), position_valor_jogador.x + sprite_valor_escolhido_jogador.width - 130, (position_valor_jogador.y) + 194, 40, WHITE);

                                }
                                else if (valor_teclado == 2)
                                {
                                    DrawText(TextFormat("%d", jogadores[0].mao[indice_empate].danger), position_valor_jogador.x + sprite_valor_escolhido_jogador.width - 130, (position_valor_jogador.y) + 194, 40, WHITE);

                                }
                                else if (valor_teclado == 3)
                                {
                                    DrawText(TextFormat("%d", jogadores[0].mao[indice_empate].mercy), position_valor_jogador.x + sprite_valor_escolhido_jogador.width - 130, (position_valor_jogador.y) + 194, 40, WHITE);

                                }

                                //DESENHANDO DO ATRIBUTO ESCOLHIDO E SEU RESPECTIVO VALOR (BOT) =-------------------------------------------------------- 
                                DrawText(atributos[valor_teclado], (position_valor_bot.x) + 75,(position_valor_bot.y) + 180, 55, WHITE);
                                if (valor_teclado == 0)
                                {
                                    DrawText(TextFormat("%d", jogadores[1].mao[indice_empate].fight), position_valor_bot.x + sprite_valor_escolhido_bot.width - 130, (position_valor_bot.y) + 194, 40, WHITE);
                                } 
                                else if (valor_teclado == 1)
                                {
                                    DrawText(TextFormat("%d", jogadores[1].mao[indice_empate].iq), position_valor_bot.x + sprite_valor_escolhido_bot.width - 130, (position_valor_bot.y) + 194, 40, WHITE);

                                }
                                else if (valor_teclado == 2)
                                {
                                    DrawText(TextFormat("%d", jogadores[1].mao[indice_empate].danger), position_valor_bot.x + sprite_valor_escolhido_bot.width - 130, (position_valor_bot.y) + 194, 40, WHITE);

                                }
                                else if (valor_teclado == 3)
                                {
                                    DrawText(TextFormat("%d", jogadores[1].mao[indice_empate].mercy), position_valor_bot.x + sprite_valor_escolhido_bot.width - 130, (position_valor_bot.y) + 194, 40, WHITE);

                                }
                            }

                            if (contador_frames >= 5 * TARGET_FPS)
                            { // 5 segundos em 60 FPS
                                acao_feita = true;
                            }
                        }
                        else if (acao_feita == true)
                        {
                        
                
                            
                            resultado_rodada = resolverRodada(jogadores, numJogadores, valor_teclado, indice_empate);
            
                            
                            if (resultado_rodada == -1)
                            {
                                
                                indice_empate++;
                                
                                // reset teclado e volta para IDLE
                                valor_teclado = -1;
                                estado_global = PICKING_UP;
                                continue;
                            }
                            
                            transferirCartas(jogadores, resultado_rodada, numJogadores, indice_empate);
                       
                            
                        
                            indice_empate = 0;
                        
                            if (resultado_rodada == 0)
                            {
                                JogadorDaVez = 0;
                            }
                            else if (resultado_rodada == 1)
                            {
                                JogadorDaVez = 1;
                            }
                            valor_teclado = -1;
                            estado_global = PICKING_UP;
                        }
                    }
                }
                else if (JogadorDaVez == 1)
                {
                    if (movimento_finalizado == false && movimento_finalizado_bot == false)
                    {
                        DrawTexture(sprite_modelo_carta_bot, position_carta_bot.x, pos_y_carta_bot - pos_y_carta_adicional_bot, WHITE);
                        if (pos_y_carta_adicional_bot >= 0)
                        {
                            pos_y_carta_adicional_bot = pos_y_carta_adicional_bot - 40;
                            if (pos_y_carta_adicional_bot == 0)
                            {
                                movimento_finalizado_bot = true;
                            }
                        }

                        // faz o movimento
                        DrawTexture(sprite_modelo_carta, position_carta.x, pos_y_carta + pos_y_carta_adicional, WHITE);
                        if (pos_y_carta_adicional >= 0)
                        {
                            pos_y_carta_adicional = pos_y_carta_adicional - 40;
                            if (pos_y_carta_adicional == 0)
                            {
                                movimento_finalizado = true;
                            }
                        }
                    }
                    else if (movimento_finalizado == true && movimento_finalizado_bot == true)
                    {
                        //GARANTIR QUE OS SPRITES NAO DESAPAREÇAM (JOGADOR) =------------------------------------------------------------------------------------------------------- //
                        // garantindo que a carta do jogador apareça no local certo
                        DrawTexture(sprites_per[jogadores[0].mao[indice_empate].imgid], position_carta.x + (4 * scale_cards), pos_y_carta + (4 * scale_cards), WHITE);
                        if (jogadores[0].mao[indice_empate].superTrunfo)
                        {
                            // modelo da carta super trunfo com opçoes bloqueadas
                            DrawTexture(sprite_modelo_carta_supertrunfo_bloqueado, position_carta.x, pos_y_carta, WHITE);
                        }
                        else
                        {
                            // modelo da carta com opçoes bloqueadas
                            DrawTexture(sprite_modelo_carta_bloqueado, position_carta.x, pos_y_carta, WHITE);
                        }
                        
                        // desenhando botoes falsos
                        Fakebutton(botao_fight, "FIGHT");   // botao fight falso
                        Fakebutton(botao_IQ, "IQ");         // botao iq falso
                        Fakebutton(botao_danger, "DANGER"); // botao danger falso
                        Fakebutton(botao_mercy, "MERCY");   // botao mercy falso
                        // mostrando o nome da carta
                        DrawText(Maiusculo(jogadores[0].mao[indice_empate].nome), (botao_fight.x) + 45, (botao_fight.y) - 70, 32, WHITE);

                        // convertendo os valores da carta para char
                        sprintf(valor_atributo_fight, "%d", jogadores[0].mao[indice_empate].fight);
                        sprintf(valor_atributo_iq, "%d", jogadores[0].mao[indice_empate].iq);
                        sprintf(valor_atributo_danger, "%d", jogadores[0].mao[indice_empate].danger);
                        sprintf(valor_atributo_mercy, "%d", jogadores[0].mao[indice_empate].mercy);

                        DrawText(Maiusculo(valor_atributo_fight), (botao_fight.x) + 325, (botao_fight.y) + 6, 32, WHITE);
                        DrawText(Maiusculo(valor_atributo_iq), (botao_IQ.x) + 325, (botao_IQ.y) + 6, 32, WHITE);
                        DrawText(Maiusculo(valor_atributo_danger), (botao_danger.x) + 325, (botao_danger.y) + 6, 32, WHITE);
                        DrawText(Maiusculo(valor_atributo_mercy), (botao_mercy.x) + 325, (botao_mercy.y) + 6, 32, WHITE);

                        DrawText(TextFormat("%c", jogadores[0].mao[indice_empate].letraClassificacao), (pos_x_carta) + 48, (pos_y_carta) + 30, 48, WHITE);
                        DrawText(TextFormat("%d", jogadores[0].mao[indice_empate].numeroClassificacao), (pos_x_carta) + 20, (pos_y_carta) + 30, 48, WHITE);
                        // ----------------------------------------------------------------------------------------------------------------------------------- //

                        // MOSTRANDO OS DADOS DAS CARTAS DO BOT =-------------------------------------------------------------
                        DrawTexture(sprites_per[jogadores[1].mao[indice_empate].imgid], position_carta_bot.x + (4 * scale_cards), pos_y_carta_bot + (4 * scale_cards), WHITE);
                        if (jogadores[1].mao[indice_empate].superTrunfo)
                        {
                            DrawTexture(sprite_modelo_carta_supertrunfo, position_carta_bot.x, pos_y_carta_bot, WHITE);
                        }
                        else
                        {
                            DrawTexture(sprite_modelo_carta_bot, position_carta_bot.x, pos_y_carta_bot, WHITE);
                        }

                        Fakebutton(botao_fight_bot, "FIGHT");   // botao fight falso
                        Fakebutton(botao_IQ_bot, "IQ");         // botao iq falso
                        Fakebutton(botao_danger_bot, "DANGER"); // botao danger falso
                        Fakebutton(botao_mercy_bot, "MERCY");   // botao mercy falso

                        DrawText(Maiusculo(jogadores[1].mao[indice_empate].nome), (botao_fight_bot.x) + 45, (botao_fight_bot.y) - 70, 32, WHITE);

                        // convertendo os valores da carta para char
                        sprintf(valor_atributo_fight_bot, "%d", jogadores[1].mao[indice_empate].fight);
                        sprintf(valor_atributo_iq_bot, "%d", jogadores[1].mao[indice_empate].iq);
                        sprintf(valor_atributo_danger_bot, "%d", jogadores[1].mao[indice_empate].danger);
                        sprintf(valor_atributo_mercy_bot, "%d", jogadores[1].mao[indice_empate].mercy);

                        DrawText(Maiusculo(valor_atributo_fight_bot), (botao_fight_bot.x) + 325, (botao_fight_bot.y) + 6, 32, WHITE);
                        DrawText(Maiusculo(valor_atributo_iq_bot), (botao_IQ_bot.x) + 325, (botao_IQ_bot.y) + 6, 32, WHITE);
                        DrawText(Maiusculo(valor_atributo_danger_bot), (botao_danger_bot.x) + 325, (botao_danger_bot.y) + 6, 32, WHITE);
                        DrawText(Maiusculo(valor_atributo_mercy_bot), (botao_mercy_bot.x) + 325, (botao_mercy_bot.y) + 6, 32, WHITE);

                        DrawText(TextFormat("%c", jogadores[1].mao[indice_empate].letraClassificacao), (pos_x_carta_bot) + 48, (pos_y_carta_bot) + 30, 48, WHITE);
                        DrawText(TextFormat("%d", jogadores[1].mao[indice_empate].numeroClassificacao), (pos_x_carta_bot) + 20, (pos_y_carta_bot) + 30, 48, WHITE);
                        // ----------------------------------------------------------------------------------------------------------------------------------- //

                            

                        if(valor_teclado == -1){
                            valor_teclado = bot(&jogadores[1]);
                        }
                          
                        resultado_rodada = resolverRodada(jogadores, numJogadores, valor_teclado, indice_empate);

                        if (acao_feita == false)
                        {
                            contador_frames++;

                            if (contador_frames >= 2 * TARGET_FPS)
                            {
                                DrawTexture(sprite_valor_escolhido_jogador, position_valor_jogador.x, position_valor_jogador.y, WHITE);
                                DrawTexture(sprite_valor_escolhido_bot, position_valor_bot.x, position_valor_bot.y, WHITE);

                                //DESENHANDO DO ATRIBUTO ESCOLHIDO E SEU RESPECTIVO VALOR (JOGADOR) =-------------------------------------------------------- 
                                DrawText(atributos[valor_teclado], (position_valor_jogador.x) + 75,(position_valor_jogador.y) + 180, 55, WHITE);
                                if (valor_teclado == 0)
                                {
                                    DrawText(TextFormat("%d", jogadores[0].mao[indice_empate].fight), position_valor_jogador.x + sprite_valor_escolhido_jogador.width - 130, (position_valor_jogador.y) + 194, 40, WHITE);
                                } 
                                else if (valor_teclado == 1)
                                {
                                    DrawText(TextFormat("%d", jogadores[0].mao[indice_empate].iq), position_valor_jogador.x + sprite_valor_escolhido_jogador.width - 130, (position_valor_jogador.y) + 194, 40, WHITE);

                                }
                                else if (valor_teclado == 2)
                                {
                                    DrawText(TextFormat("%d", jogadores[0].mao[indice_empate].danger), position_valor_jogador.x + sprite_valor_escolhido_jogador.width - 130, (position_valor_jogador.y) + 194, 40, WHITE);

                                }
                                else if (valor_teclado == 3)
                                {
                                    DrawText(TextFormat("%d", jogadores[0].mao[indice_empate].mercy), position_valor_jogador.x + sprite_valor_escolhido_jogador.width - 130, (position_valor_jogador.y) + 194, 40, WHITE);

                                }

                                //DESENHANDO DO ATRIBUTO ESCOLHIDO E SEU RESPECTIVO VALOR (BOT) =-------------------------------------------------------- 
                                DrawText(atributos[valor_teclado], (position_valor_bot.x) + 75,(position_valor_bot.y) + 180, 55, WHITE);
                                if (valor_teclado == 0)
                                {
                                    DrawText(TextFormat("%d", jogadores[1].mao[indice_empate].fight), position_valor_bot.x + sprite_valor_escolhido_bot.width - 130, (position_valor_bot.y) + 194, 40, WHITE);
                                } 
                                else if (valor_teclado == 1)
                                {
                                    DrawText(TextFormat("%d", jogadores[1].mao[indice_empate].iq), position_valor_bot.x + sprite_valor_escolhido_bot.width - 130, (position_valor_bot.y) + 194, 40, WHITE);

                                }
                                else if (valor_teclado == 2)
                                {
                                    DrawText(TextFormat("%d", jogadores[1].mao[indice_empate].danger), position_valor_bot.x + sprite_valor_escolhido_bot.width - 130, (position_valor_bot.y) + 194, 40, WHITE);

                                }
                                else if (valor_teclado == 3)
                                {
                                    DrawText(TextFormat("%d", jogadores[1].mao[indice_empate].mercy), position_valor_bot.x + sprite_valor_escolhido_bot.width - 130, (position_valor_bot.y) + 194, 40, WHITE);

                                }
                            }

                            if (contador_frames >= 5 * TARGET_FPS)
                            { // 5 segundos em 60 FPS
                                acao_feita = true;
                            }
                        }
                        else if (acao_feita == true)
                        {
                            
                            
                            if (resultado_rodada == -1)
                            {
                                indice_empate++;
                                valor_teclado = -1;
                                estado_global = PROCESSAR_RODADA;
                                continue;
                            }
                            
                            transferirCartas(jogadores, resultado_rodada, numJogadores, indice_empate); // Passar o índice do vencedor
                            indice_empate = 0;
                            
                            valor_teclado = -1;
                            
                            if (resultado_rodada == 0)
                            {
                                JogadorDaVez = 0;
                            }
                            else if (resultado_rodada == 1)
                            {
                                JogadorDaVez = 1;
                            }
                            
                            estado_global = PICKING_UP;
                        }
                    }
                }

                ganhador = verificarFimDoJogo(jogadores, numJogadores, indice_empate);
                if (ganhador != -1)
                {
                    tela_jogo = GAME_OVER;
                }

            break;

            case IDLE_WITH_CARD: // PARTE ONDE SERAO MOSTRADAS AS CARTAS E VEREMOS QUEM VENCE A CADA ATRIBUTO ESCOLHIDO =-------------------

                sprintf(numero_de_cartas_p1, "%d", jogadores[0].cartasRestantes);
                sprintf(numero_de_cartas_p2, "%d", jogadores[1].cartasRestantes);

                DrawText(numero_de_cartas_p1, ((float)screenWidth / 2.f) - 36, ((float)screenHeight / 2.f) + 370, 90, WHITE);
                DrawText(numero_de_cartas_p2, ((float)screenWidth / 2.f) - 36, ((float)screenHeight / 2.f) - 443, 90, WHITE);

                // ANIMAÇÃO DO BOT PARADO COM A CARTA
                Animacao(sprite_bot_idle_with_card, 4, &frame_idle_with_card, &source_idle_with_card, position_bot, updatetime, &runningtime_idle_with_card);

                if (JogadorDaVez == 0)
                {
                    // se o movimento da carta nao foi feita
                    if (movimento_finalizado == false)
                    {
                        // faz o movimento
                        DrawTexture(sprite_modelo_carta, position_carta.x, pos_y_carta + pos_y_carta_adicional, WHITE);
                        if (pos_y_carta_adicional >= 0)
                        {
                            pos_y_carta_adicional = pos_y_carta_adicional - 40;
                            if (pos_y_carta_adicional == 0)
                            {
                                movimento_finalizado = true;
                            }
                        }
                    }
                    else // Se o movimento foi feito:
                    {
                        // garantindo que a carta do jogador apareça no local certo
                        DrawTexture(sprites_per[jogadores[0].mao[indice_empate].imgid], position_carta.x + (4 * scale_cards), pos_y_carta + (4 * scale_cards), WHITE);
                        if (jogadores[0].mao[indice_empate].superTrunfo)
                        {
                            DrawTexture(sprite_modelo_carta_supertrunfo, position_carta.x, pos_y_carta, WHITE);
                        }
                        else
                        {
                            DrawTexture(sprite_modelo_carta, position_carta.x, pos_y_carta, WHITE);
                        }
                        // mostrando o nome da carta
                        DrawText(Maiusculo(jogadores[0].mao[indice_empate].nome), (botao_fight.x) + 45, (botao_fight.y) - 70, 32, WHITE);

                        // convertendo os valores da carta para char
                        sprintf(valor_atributo_fight, "%d", jogadores[0].mao[indice_empate].fight);
                        sprintf(valor_atributo_iq, "%d", jogadores[0].mao[indice_empate].iq);
                        sprintf(valor_atributo_danger, "%d", jogadores[0].mao[indice_empate].danger);
                        sprintf(valor_atributo_mercy, "%d", jogadores[0].mao[indice_empate].mercy);

                        DrawText(Maiusculo(valor_atributo_fight), (botao_fight.x) + 325, (botao_fight.y) + 6, 32, WHITE);
                        DrawText(Maiusculo(valor_atributo_iq), (botao_IQ.x) + 325, (botao_IQ.y) + 6, 32, WHITE);
                        DrawText(Maiusculo(valor_atributo_danger), (botao_danger.x) + 325, (botao_danger.y) + 6, 32, WHITE);
                        DrawText(Maiusculo(valor_atributo_mercy), (botao_mercy.x) + 325, (botao_mercy.y) + 6, 32, WHITE);

                        DrawText(TextFormat("%c", jogadores[0].mao[indice_empate].letraClassificacao), (pos_x_carta) + 48, (pos_y_carta) + 30, 48, WHITE);
                        DrawText(TextFormat("%d", jogadores[0].mao[indice_empate].numeroClassificacao), (pos_x_carta) + 20, (pos_y_carta) + 30, 48, WHITE);

                        // colocando um botao de fight
                        if (DrawblankButton(botao_fight, "FIGHT") && valor_teclado == -1)
                        {
                            Tocar_Som(snd_select, efeitos_sonoros_ligados);
                            valor_teclado = 0;
                        }
                        // colocando um botao de IQ
                        if (DrawblankButton(botao_IQ, "IQ") && valor_teclado == -1)
                        {
                            Tocar_Som(snd_select, efeitos_sonoros_ligados);
                            valor_teclado = 1;
                        }
                        // colocando um botao de danger
                        if (DrawblankButton(botao_danger, "DANGER") && valor_teclado == -1)
                        {
                            Tocar_Som(snd_select, efeitos_sonoros_ligados);
                            valor_teclado = 2;
                        }
                        // colocando um botao de mercy
                        if (DrawblankButton(botao_mercy, "MERCY") && valor_teclado == -1)
                        {
                            Tocar_Som(snd_select, efeitos_sonoros_ligados);
                            valor_teclado = 3;
                        }

                        if (valor_teclado != -1)
                        {
                            estado_global = PROCESSAR_RODADA;
                        }
                    }
                }
                else if (JogadorDaVez == 1)
                {
                    estado_global = PROCESSAR_RODADA;
                }    
            }
            break; // IDLE_WITH_CARD

        case MENU_PAUSE:
            DrawTexture(sprite_background_menu, pos_x_menu, pos_y_menu, WHITE);

            // RETORNAR =------------------------------------------------------------------------------
            if (DrawBlackButton(botao_return, "RETORNAR")) // MUDA DE TELA
            {
                Tocar_Som(snd_select, efeitos_sonoros_ligados);

                if (tela_game == true)
                {
                    tela_jogo = GAME;
                }
                else if (tela_game_over == true)
                {
                    tela_jogo = GAME_OVER;
                }
            }

            // MUSICA =---------------------------------------------------------------------------------
            //  Botão da musica
            if (DrawBlackButton(botao_musica, "MUSICA")) // liga e desliga o som do jogo
            {
                Tocar_Som(snd_select, efeitos_sonoros_ligados);
                if (musica_ligada == false) // se o botao for apertado e a musica estiver desligado
                {
                    PlayMusicStream(bot_theme);     // ele liga
                    musica_ligada = !musica_ligada; // sinal muda pra ligado
                }
                else
                {                                   // se nao
                    StopMusicStream(bot_theme);     // ele desliga
                    musica_ligada = !musica_ligada; // sinal muda pra desligado
                }
            }

            // slider da musica
            if (musica_ligada == true)
            {
                if (DrawBlackSlider(slider_musica, "Min", "Max", &volume_musica, 0.f, 2.5f))
                {
                    SetMusicVolume(bot_theme, volume_musica);
                }
            }

            // EFEITOS SONOROS =-------------------------------------------------------------------------------------
            //  Botão dos efeitos sonoros
            if (DrawBlackButton(botao_sounds_effects, "EFEITOS SONOROS")) // liga e desliga o som do jogo
            {
                Tocar_Som(snd_select, efeitos_sonoros_ligados);
                if (efeitos_sonoros_ligados == false) // se o botao for apertado e os efeitos sonoros estiverem desligados
                {
                    efeitos_sonoros_ligados = !efeitos_sonoros_ligados; // sinal muda pra ligado
                }
                else
                {                                                       // se nao
                    efeitos_sonoros_ligados = !efeitos_sonoros_ligados; // sinal muda pra desligado
                }
            }

            // slider dos efeitos sonoros
            if (efeitos_sonoros_ligados == true)
            {
                if (DrawBlackSlider(slider_efeitos_sonoros, "Min", "Max", &volume_sound, 0.f, 2.5f))
                {
                    SetSoundVolume(snd_select, volume_sound);
                }
            }

            // SAIR =-------------------------------------------------------------------------------------------------
            //  Botão sair
            if (DrawBlackButton(botao_sair, "SAIR")) // FECHA O JOGO
            {
                Tocar_Som(snd_select, efeitos_sonoros_ligados);
                desliga = true;
                if (desliga == true)
                {
                    break;
                }
            }

        break;

        case GAME_OVER:

            if (ganhador == 0) // Se o jogador ganhar o jogo
            {
                DrawTexture(sprite_background_win, pos_x_win, pos_y_win, WHITE);
            }
            else
            { // Se o jogador perder o jogo
                DrawTexture(sprite_background_game_over, pos_x_game_over, pos_y_game_over, WHITE);
            }

            // Garantindo que a tela atual é a do GAME_OVER/WIN
            tela_game = false;
            tela_game_over = true;

            if (IsKeyPressed(KEY_V))
                tela_jogo = MENU_PAUSE;

           

            // SAIR =-------------------------------------------------------------------------------------------------
            //  Botão sair
            if (DrawBlackButton(botao_sair_game_over, "SAIR")) // FECHA O JOGO
            {
                Tocar_Som(snd_select, efeitos_sonoros_ligados);
                desliga = true;
                if (desliga == true)
                {
                    break;
                }
            }

        break;
        }
        EndDrawing();
    }

    // Tirando todas as musicas e sons =-----
    StopMusicStream(bot_theme);   // parando a musica do bot
    UnloadMusicStream(bot_theme); // tirando a musica do bot
    UnloadSound(snd_select);      // tirando os efeitos sonoros

    // Tirando todas as texturas =-----
    // sprites do deck
    UnloadTexture(sprite_deck);            // sprite do deck do jogador
    UnloadTexture(sprite_deck_picking_up); // sprite_sheet da carta sendo pega do deck do jogador
    UnloadTexture(sprite_deck_counter);    // sprite do contador de cartas

    // sprites das cartas
    UnloadTexture(sprite_modelo_carta);                         // sprite da carta do jogador
    UnloadTexture(sprite_modelo_carta_supertrunfo);             // sprite da carta supertrunfo
    UnloadTexture(sprite_modelo_carta_bloqueado);               // sprite da carta bloqueada
    UnloadTexture(sprite_modelo_carta_supertrunfo_bloqueado);   // sprite da carta supertrunfo
    UnloadTexture(sprite_modelo_carta_bot);                     // sprite da carta do bot

    // sprites personagens
    for (int i = 0; i >= totalCartas; i++)
    {
        UnloadTexture(sprites_per[i]);
    }

    // sprites do bot
    UnloadTexture(sprite_bot_idle);           // sprite_sheet do bot parado
    UnloadTexture(sprite_bot_picking_up);     // sprite_sheet do bot pegando carta
    UnloadTexture(sprite_bot_idle_with_card); // sprite_sheet do bot parado com a carta

    // backgrounds
    UnloadTexture(sprite_background);           // background da partida
    UnloadTexture(sprite_background_menu);      // background do menu de pause
    UnloadTexture(sprite_background_win);       // background da tela de win
    UnloadTexture(sprite_background_game_over); // background da tela de game over
    UnloadTexture(sprite_loading_background);   // background da tela de loading

    // Fechando o sistema de audio =-----
    CloseAudioDevice();

    // Fechando a janela =-----
    CloseWindow();
    return 0;
}
