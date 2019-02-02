#include "Led.h"
#include "Bouton.h"
#include "Son.h"

Led led1;
Bouton button1;
Son speaker1;

void action(int note,float duree)
{
    led1.allume();
    speaker1.sonne(note);
    attendre(duree);
    speaker1.arreteDeSonner();
    led1.eteint();
}

class Sequence
{
    public:
        Sequence();
        Sequence(int tempo, int resolution);
        
        int bpm;
        float ronde;
        int resolution_mesure;
        // int pas[];
        int pas[16] = {220,220,220,0,220,0,0,0,220,220,220,0,220,0,0,0};

        void jouer() const;
};
Sequence::Sequence(int tempo, int resolution)
{
    bpm = tempo;
    ronde = tempo/60*1000;
    resolution_mesure = resolution;
    // pas = int pas[resolution];
}
void Sequence::jouer() const
{
    for(int i = 0; i < resolution_mesure; i++)
    {
        if (pas[i] > 0){
            action(pas[i], ronde/resolution_mesure);
        } else {
            attendre(ronde/resolution_mesure);
        }
    }
}

// ------------------------------------------------ //
// ----- Utilisation de la classe en contexte ----- //
// Sequence *nom*(*Tempo*, *Resolution de la mesure, nombre de pas*);
// ------------------------------------------------ //

Sequence sequence1(128, 16);

void setup()
{
    // Ici on compose
    // sequence1.pas = {220,0,220,0,220,0,220,0};
    
    led1.allume();
    attendre(1*1000);
    led1.eteint();
}

void loop()
{
    if (button1.aEteAppuye()) {
        // Ici on joue notre séquence une fois
        sequence1.jouer();
    }
}
