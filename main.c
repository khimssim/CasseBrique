#include "header.h"


int main(int argc, char *argv[])
{

     game myGame;
     gameState state;
     int touches[2];
     Paddle joueur;
     balle Balle;
     brique Briques[16][15];  //initialisation du tableau pour afficher les briques

    //Pour les 60 fps
    unsigned int frameLimit = SDL_GetTicks() + 16;


    if(init("Casse brique",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN,&myGame)){

                state.g_bRunning=1;


    }else{

            return 1;

    }


   state.right=1;
   state.left=0;

    InitPaddle(&joueur);
    InitBalle(&Balle);
    InitBriques(Briques);
   // collisionBrique(&Balle,Briques);

    while(state.g_bRunning){

           handleEvents(&state, touches);
           DeplacementPaddle(touches,&joueur);
           AffichePaddle(&myGame,state,&joueur);
           AfficheMur(&myGame,state);
           AfficheMurHaut(&myGame,state);
           CollisionBalle(&Balle,&joueur);
           DeplacementBalle(&Balle);
           AfficheBalle(&myGame,state,&Balle);
           AfficheBriques(&myGame,state,Briques);

           SDL_RenderPresent(myGame.g_pRenderer);
           SDL_RenderClear(myGame.g_pRenderer);


        // Gestion des 60 fps (1000ms/60 = 16.6 -> 16
            delay(frameLimit);
            frameLimit = SDL_GetTicks() + 16;


    }

        destroy(&myGame);

        SDL_Quit();




  return 0;
}

void InitPaddle(Paddle *joueur){

    joueur->position.x=SCREEN_WIDTH/2-64;
    joueur->position.y=SCREEN_HEIGHT-32;
    joueur->vitesse=5;
    joueur->hauteur=32;
    joueur->largeur=128;


}
//affichage du paddle
void AffichePaddle(game *myGame,gameState state, Paddle *joueur){

        SDL_Rect rectangleDest;
        SDL_Rect rectangleSource;


        myGame->g_surface = IMG_Load("./assets/paddle.png");//Chargement de l'image bitmap

         if(!myGame->g_surface) {
            fprintf(stdout,"IMG_Load: %s\n", SDL_GetError());
            // handle error
        }

        if(myGame->g_surface){

                 myGame->g_texture = SDL_CreateTextureFromSurface(myGame->g_pRenderer,myGame->g_surface); // Préparation du sprite
                 SDL_FreeSurface(myGame->g_surface); // Libération de la ressource occupée par le sprite

                if(myGame->g_texture){

                    //gestion des animations
                    rectangleSource.x=0;
                    rectangleSource.y=0;
                    rectangleSource.w=joueur->largeur;
                    rectangleSource.h=joueur->hauteur;



                    //Définition du rectangle dest pour dessiner Bitmap
                    rectangleDest.x=joueur->position.x;//debut x
                    rectangleDest.y=joueur->position.y;//debut y
                    rectangleDest.w=rectangleSource.w; //Largeur
                    rectangleDest.h=rectangleSource.h; //Hauteur

                    SDL_RenderCopy(myGame->g_pRenderer,myGame->g_texture,&rectangleSource,&rectangleDest);

                }

                else{
                        fprintf(stdout,"Échec de création de la texture (%s)\n",SDL_GetError());
                }



        }else{
            fprintf(stdout,"Échec de chargement du sprite (%s)\n",SDL_GetError());
        }

    destroyTexture(myGame);


}

//géstion du déplacement du paddle
void DeplacementPaddle(int touches[2],Paddle *joueur){

    if ((touches[0]==1) && (CollisionPaddle(joueur)!=gauche)){

        joueur->position.x-=joueur->vitesse;

    }
    else if ((touches[1]==1) && (CollisionPaddle(joueur)!=droite)){
        joueur->position.x+=joueur->vitesse;
    }

}


//collision du paddle
int CollisionPaddle(Paddle *joueur){

    if (joueur->position.x>=SCREEN_WIDTH-144){

        return droite;

    }else if (joueur->position.x<=16){

        return gauche;
    }

    return 0;

}

//initialisation de la balle
void InitBalle(balle *Balle){

    Balle->position.x=SCREEN_WIDTH/2-24;
    Balle->position.y=SCREEN_HEIGHT/2-24;
    Balle->vitesse=5;
    Balle->hauteur=24;
    Balle->largeur=24;
    Balle->haut_bas=0;
    Balle->gauche_droite=0;


}


//affichage de la balle
void AfficheBalle(game *myGame,gameState state,balle *Balle){

        SDL_Rect rectangleDest;
        SDL_Rect rectangleSource;


        myGame->g_surface = IMG_Load("./assets/ball.png");//Chargement de l'image bitmap

         if(!myGame->g_surface) {
            fprintf(stdout,"IMG_Load: %s\n", SDL_GetError());
            // handle error
        }

        if(myGame->g_surface){

                 myGame->g_texture = SDL_CreateTextureFromSurface(myGame->g_pRenderer,myGame->g_surface); // Préparation du sprite
                 SDL_FreeSurface(myGame->g_surface); // Libération de la ressource occupée par le sprite

                if(myGame->g_texture){

                    //gestion des animations
                    rectangleSource.x=0;
                    rectangleSource.y=0;
                    rectangleSource.w=Balle->largeur;
                    rectangleSource.h=Balle->hauteur;



                    //Définition du rectangle dest pour dessiner Bitmap
                    rectangleDest.x=Balle->position.x;//debut x
                    rectangleDest.y=Balle->position.y;//debut y
                    rectangleDest.w=rectangleSource.w; //Largeur
                    rectangleDest.h=rectangleSource.h; //Hauteur

                    SDL_RenderCopy(myGame->g_pRenderer,myGame->g_texture,&rectangleSource,&rectangleDest);

                }

                else{
                        fprintf(stdout,"Échec de création de la texture (%s)\n",SDL_GetError());
                }



        }else{
            fprintf(stdout,"Échec de chargement du sprite (%s)\n",SDL_GetError());
        }

    destroyTexture(myGame);


}


//gestion du déplacement de la balle

void DeplacementBalle(balle *Balle){

    if (Balle->haut_bas==1){

        Balle->position.y+=Balle->vitesse;

    }
    else if (Balle->haut_bas==0){

        Balle->position.y-=Balle->vitesse;

    }

    if (Balle->gauche_droite==1){

        Balle->position.x+=Balle->vitesse;
    }
    else if (Balle->gauche_droite==0){

        Balle->position.x-=Balle->vitesse;
    }

}

//gestion des collisions de la balle sur le paddle et les sides
void CollisionBalle(balle *Balle, Paddle *joueur){



    if (Balle->position.x>=SCREEN_WIDTH-40){

        Balle->gauche_droite=0;

    }else if (Balle->position.x<=16){

        Balle->gauche_droite=1;
    }

    if ((Balle->position.y+16>=joueur->position.y) && (Balle->position.x>=joueur->position.x) && (Balle->position.x+16<=joueur->position.x+128)){

        Balle->haut_bas=0;

    }else if (Balle->position.y<=0){

        Balle->haut_bas=1;
    }

}


/* je voulais faire la collision avec les briques, je voulais vérifier quand le x,y de la balle
entre en collision avec le x,y de la brique alors on détruit la texture.
Mais je n'ai pas réussi à le faire */

/*void collisionBrique(balle *Balle, brique Briques[10] [10])
{


}*/


//initialisation des briques
void InitBriques(brique Briques[10][10]){

    int i;
    int j;

    for (i=0;i<10;i++){
        for (j=0;j<10;j++){

            Briques[i][j].hauteur=24;
            Briques[i][j].largeur=64;
            Briques[i][j].position.x=182+i*Briques[i][j].largeur;
            Briques[i][j].position.y=32+j*Briques[i][j].hauteur;

        }
    }


}


//affichage des briques
void AfficheBriques(game *myGame,gameState state, brique Briques[10][10]){


        int i;
        int j;

        SDL_Rect rectangleDest;
        SDL_Rect rectangleSource;


        myGame->g_surface = IMG_Load("./assets/bricks.png");//Chargement de l'image bitmap

         if(!myGame->g_surface) {
            fprintf(stdout,"IMG_Load: %s\n", SDL_GetError());
            // handle error
        }

        if(myGame->g_surface){

                 myGame->g_texture = SDL_CreateTextureFromSurface(myGame->g_pRenderer,myGame->g_surface); // Préparation du sprite
                 SDL_FreeSurface(myGame->g_surface); // Libération de la ressource occupée par le sprite

                if(myGame->g_texture){



                    for (i=0;i<10;i++){
                        for (j=0;j<10;j++){

                            //gestion des animations
                            rectangleSource.x=64;
                            rectangleSource.y=24;
                            rectangleSource.w=Briques[i][j].largeur;
                            rectangleSource.h=Briques[i][j].hauteur;



                            //Définition du rectangle dest pour dessiner Bitmap
                            rectangleDest.x=Briques[i][j].position.x;//debut x
                            rectangleDest.y=Briques[i][j].position.y;//debut y
                            rectangleDest.w=rectangleSource.w; //Largeur
                            rectangleDest.h=rectangleSource.h; //Hauteur

                            SDL_RenderCopy(myGame->g_pRenderer,myGame->g_texture,&rectangleSource,&rectangleDest);
                        }
                    }

                }

                else{
                        fprintf(stdout,"Échec de création de la texture (%s)\n",SDL_GetError());
                }



        }else{
            fprintf(stdout,"Échec de chargement du sprite (%s)\n",SDL_GetError());
        }

    destroyTexture(myGame);


}


//initialisation de la SDL
int init(char *title, int xpos,int ypos,int height, int width,int flags,game *myGame){


    //initialize SDL

    if(SDL_Init(SDL_INIT_EVERYTHING)>=0)
    {
            //if succeeded create our window
            myGame->g_pWindow=SDL_CreateWindow(title,xpos,ypos,height,width,flags);
            //if succeeded create window, create our render
            if(myGame->g_pWindow!=NULL){
                myGame->g_pRenderer=SDL_CreateRenderer(myGame->g_pWindow,-1,SDL_RENDERER_ACCELERATED);


            }


    }else{


        return 0;
    }




    return 1;


}


//gestion des évènements
void handleEvents(gameState *state, int touches[2]){


    SDL_Event event;

    if(SDL_PollEvent(&event)){
        switch(event.type){
        case SDL_QUIT:
              state->g_bRunning=0;break;
        case SDL_KEYDOWN:
                        switch (event.key.keysym.sym)
                            {
                                case SDLK_LEFT:touches[0]=1; break;
                                case SDLK_RIGHT:touches[1]=1 ; break;
                                case SDLK_UP:    ; break;
                                case SDLK_DOWN:  ; break;
                            }
                            break;

        case SDL_KEYUP:
                        switch (event.key.keysym.sym)
                            {
                                case SDLK_LEFT:touches[0]=0; break;
                                case SDLK_RIGHT:touches[1]=0 ; break;
                                case SDLK_UP:    ; break;
                                case SDLK_DOWN:  ; break;
                            }
                            break;


        default:break;

        }
    }


}

//affichage des sides
void AfficheMur(game *myGame,gameState state){

        SDL_Rect rectangleDest;
        SDL_Rect rectangleSource;

        SDL_Rect rectangleDest2;
        SDL_Rect rectangleSource2;


        myGame->g_surface = IMG_Load("./assets/side.png");//Chargement de l'image bitmap

         if(!myGame->g_surface) {
            fprintf(stdout,"IMG_Load: %s\n", SDL_GetError());
            // handle error
        }

        if(myGame->g_surface){

                 myGame->g_texture = SDL_CreateTextureFromSurface(myGame->g_pRenderer,myGame->g_surface); // Préparation du sprite
                 SDL_FreeSurface(myGame->g_surface); // Libération de la ressource occupée par le sprite

                if(myGame->g_texture){
                    //mur1
                    //gestion des animations
                    rectangleSource.x=0;
                    rectangleSource.y=0;
                    rectangleSource.w=16;//1 image = w:128 et h:82
                    rectangleSource.h=SCREEN_HEIGHT;



                    //Définition du rectangle dest pour dessiner Bitmap
                    rectangleDest.x=0;//debut x
                    rectangleDest.y=0;//debut y
                    rectangleDest.w=rectangleSource.w; //Largeur
                    rectangleDest.h=rectangleSource.h; //Hauteur


                    //mur2
                    //gestion des animations
                    rectangleSource2.x=0;
                    rectangleSource2.y=0;
                    rectangleSource2.w=16;//1 image = w:128 et h:82
                    rectangleSource2.h=SCREEN_HEIGHT;



                    //Définition du rectangle dest pour dessiner Bitmap
                    rectangleDest2.x=SCREEN_WIDTH-16;//debut x
                    rectangleDest2.y=0;//debut y
                    rectangleDest2.w=rectangleSource2.w; //Largeur
                    rectangleDest2.h=rectangleSource2.h; //Hauteur


                    SDL_RenderCopy(myGame->g_pRenderer,myGame->g_texture,&rectangleSource,&rectangleDest);

                    SDL_RenderCopy(myGame->g_pRenderer,myGame->g_texture,&rectangleSource2,&rectangleDest2);


                }

                else{
                        fprintf(stdout,"Échec de création de la texture (%s)\n",SDL_GetError());
                }



        }else{
            fprintf(stdout,"Échec de chargement du sprite (%s)\n",SDL_GetError());
        }

    destroyTexture(myGame);


}


//affichage du side haut
void AfficheMurHaut(game *myGame,gameState state)
{
        SDL_Rect rectangleDest;
        SDL_Rect rectangleSource;



        myGame->g_surface = IMG_Load("./assets/sideHaut.png");//Chargement de l'image bitmap

         if(!myGame->g_surface) {
            fprintf(stdout,"IMG_Load: %s\n", SDL_GetError());
            // handle error
        }

        if(myGame->g_surface){

                 myGame->g_texture = SDL_CreateTextureFromSurface(myGame->g_pRenderer,myGame->g_surface); // Préparation du sprite
                 SDL_FreeSurface(myGame->g_surface); // Libération de la ressource occupée par le sprite

                if(myGame->g_texture){
                    //mur1
                    //gestion des animations
                    rectangleSource.x=0;
                    rectangleSource.y=0;
                    rectangleSource.w=993;
                    rectangleSource.h=16;



                    //Définition du rectangle dest pour dessiner Bitmap
                    rectangleDest.x=16;//debut x
                    rectangleDest.y=0;//debut y
                    rectangleDest.w=rectangleSource.w; //Largeur
                    rectangleDest.h=rectangleSource.h; //Hauteur



                    SDL_RenderCopy(myGame->g_pRenderer,myGame->g_texture,&rectangleSource,&rectangleDest);


                }

                else{
                        fprintf(stdout,"Échec de création de la texture (%s)\n",SDL_GetError());
                }



        }else{
            fprintf(stdout,"Échec de chargement du sprite (%s)\n",SDL_GetError());
        }

    destroyTexture(myGame);
}


void delay(unsigned int frameLimit){
    // Gestion des 60 fps (images/seconde)
    unsigned int ticks = SDL_GetTicks();

    if (frameLimit < ticks)
    {
        return;
    }

    if (frameLimit > ticks + 16)
    {
        SDL_Delay(16);
    }

    else
    {
        SDL_Delay(frameLimit - ticks);
    }
}




void destroy(game *myGame){


    //Destroy render
    if(myGame->g_pRenderer!=NULL)
        SDL_DestroyRenderer(myGame->g_pRenderer);


    //Destroy window
    if(myGame->g_pWindow!=NULL)
        SDL_DestroyWindow(myGame->g_pWindow);

}



void destroyTexture(game *myGame){


    //Destroy texture
    if(myGame->g_texture!=NULL)
            SDL_DestroyTexture(myGame->g_texture);

}



