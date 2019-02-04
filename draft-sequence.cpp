#include "Led.h"
#include "Bouton.h"
#include "Son.h"

Led led1;
Bouton button1;
Bouton button2;
Bouton button3;
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
        void composer(int * composition);
};
Sequence::Sequence(int tempo, int resolution)
{
    bpm = tempo;
    // ronde = 60/bpm*4*1000;
    ronde = bpm/60*1000;
    resolution_mesure = resolution;
    // pas = int pas[resolution];
}
void Sequence::jouer() const
{
    for(int i = 0; i < resolution_mesure; i++)
    {
        if (pas[i] > 0){
            action(pas[i]/2, ronde/resolution_mesure);
        } else {
            attendre(ronde/resolution_mesure);
        }
    }
}
void Sequence::composer(int * composition)
{
    // pas = new int[resolution_mesure]composition;
    // pas = new int[resolution_mesure];
    
    // for(int i = 0; i < composition.size(); i++)
    // {
    //     pas[i] = composition[i];
    // }
}

// ------------------------------------------------ //
// ----- Utilisation de la classe en contexte ----- //
// ------------------------------------------------ //

// int tempo = 128;
int global_tempo = 120;

Sequence sequence1(global_tempo, 4);
Sequence sequence2(global_tempo, 8);
Sequence sequence3(global_tempo, 16);
Sequence sequence4(global_tempo, 16);
Sequence sequence5(global_tempo, 16);
Sequence sequence6(global_tempo, 16);

void setup()
{
    // Ici on compose
    // sequence1.composer(new int[] = {110,0,220,0,110,0,220,0});
    sequence1.pas = new int[sequence1.resolution_mesure]{196,174.61,196,196};
    sequence2.pas = new int[sequence2.resolution_mesure]{196,196,196,0,
                                                        196,196,196,0};
    sequence3.pas = new int[sequence3.resolution_mesure]{293.66,293.66,293.66,0,
                                                        293.66,349.23,0,293.66,
                                                        0,293.66,587.33,0,
                                                        0,698.46,698.46,0
    };
    sequence4.pas = new int[sequence4.resolution_mesure]{349.23,349.23,392,392,
                                                        392,392,392,349.23,
                                                        349.23,392,392,392,
                                                        392,0,0,0
    };
    sequence5.pas = new int[sequence5.resolution_mesure]{293.66,293.66,293.66,0,
                                                        293.66,587.33,0,293.66,
                                                        0,293.66,587.33,0,
                                                        0,0,0,0
    };
    sequence6.pas = new int[sequence6.resolution_mesure]{293.66,293.66,587.33,0,
                                                        293.66,293.66,587.33,0,
                                                        293.66,293.66,587.33,0,
                                                        293.66,293.66,587.33,0
    };

    // double * arr = new double[3]{1,2,3};
    led1.allume();
    speaker1.sonne(440);
    attendre(1*1000);
    speaker1.arreteDeSonner();
    led1.eteint();
}

void loop()
{
    if (button1.aEteAppuye()) {
        sequence1.jouer();
        sequence2.jouer();
        sequence2.jouer();
        sequence2.jouer();
    }
    if (button2.aEteAppuye()) {
        sequence3.jouer();
        sequence3.jouer();
        sequence3.jouer();
        sequence4.jouer();
    }
    if (button3.aEteAppuye()) {
        sequence5.jouer();
        sequence5.jouer();
        sequence3.jouer();
        sequence6.jouer();
    }
}
