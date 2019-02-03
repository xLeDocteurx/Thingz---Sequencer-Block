#include "Led.h"
#include "Bouton.h"
#include "Son.h"

Led led1;
Bouton button1;
Bouton button2;
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
        int * pas;

        void jouer() const;
        void composer();
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
void Sequence::composer()
{
    // pas = new int[]{};
}

// ------------------------------------------------ //
// ----- Utilisation de la classe en contexte ----- //
// ------------------------------------------------ //

Sequence sequence1(128, 8);
Sequence sequence2(128, 16);

void setup()
{
    // Ici on compose
    sequence1.pas = new int[sequence1.resolution_mesure]{110,0,220,0,110,0,220,0};
    sequence2.pas = new int[sequence2.resolution_mesure]{110,110,220,0,110,0,220,0,110,220,220,0,110,0,220,0};

    // double * arr = new double[3]{1,2,3};
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
    if (button2.aEteAppuye()) {
        // Ici on joue notre séquence une fois
        sequence2.jouer();
    }
}
