// James Blades (BetaWar)
// dreamincode.net
#ifndef RUNNABLE_H
#define	RUNNABLE_H

// just an interface
class Runnable{
protected:
public:
    bool ceaseThread;
    bool killThread;
    virtual void tick(void) = 0;
    virtual void tack(void) = 0;
};


#endif	/* RUNNABLE_H */
