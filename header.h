#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <time.h>


#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 780

//Option de build dans les linker setting mettre les libSDL2main.a libSDL2.dll.a
//Dans search directory
//Option de build compiler mettre les include
//Option de build linker mettre les lib

//mettre dans build linker -lmingw32

typedef struct game{


     SDL_Window *g_pWindow;
     SDL_Renderer *g_pRenderer;
     SDL_Texture *g_texture;
     SDL_Surface *g_surface;


}game;

typedef struct gameState{

    int g_bRunning;
    int left;
    int right;


}gameState;

//type structuré des coordonnées x et y
typedef struct coordonnees{

    double x;
    double y;



}coordonnees;


// type structuré du paddle
typedef struct Paddle{

    coordonnees position;
    double vitesse;
    double hauteur;
    double largeur;

}Paddle;


//type structuré de la balle
typedef struct balle{

    coordonnees position;
    double vitesse;
    double hauteur;
    double largeur;
    int haut_bas;
    int gauche_droite;

}balle;


//type structuré des briques
typedef struct brique{

    coordonnees position;
    double hauteur;
    double largeur;
    int destroy;

}brique;

//collisions
enum collision{

    haut,bas,gauche,droite
};

// les prototypes
int init(char *title, int xpos,int ypos,int height, int width,int flags,game *myGame);
void cutBitmapTexture(game *myGame,gameState state);
void delay(unsigned int frameLimit);
void destroyTexture(game *myGame);
void destroy(game *myGame);
void AffichePaddle(game *myGame,gameState state, Paddle *joueur);
void DeplacementPaddle(int touches[2],Paddle *joueur);
void handleEvents(gameState *state, int touches[2]);
void InitPaddle(Paddle *joueur);
int CollisionPaddle(Paddle *joueur);
void AfficheMur(game *myGame,gameState state);
void AfficheMurHaut(game *myGame,gameState state);
void InitBalle(balle *Balle);
void AfficheBalle(game *myGame,gameState state,balle *Balle);
void CollisionBalle(balle *Balle, Paddle *joueur);
void collisionBrique(balle *Balle,brique Briques[10][10]);
void DeplacementBalle(balle *Balle);
void InitBriques(brique Briques[10][10]);
void AfficheBriques(game *myGame,gameState state, brique Briques[10][10]);
