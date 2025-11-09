#ifndef DEMONIC_H
#define DEMONIC_H
#include "Character.h"
#include "Animation.h"
#include "RigidBody.h"

class Demonic: public Character{
    public:
        Demonic(Properties *props);

        virtual void Draw();
        virtual void Update(float dt);
        virtual void Clean();
    protected:

    private:
        Animation *m_Animation;
        RigidBody *m_RigidBody;
};

#endif // DEMONIC_H
