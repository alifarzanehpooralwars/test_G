#pragma once

#include "QBBC.hh"
#include "QGSP_BIC_HP.hh"

class PhysicsList : public QGSP_BIC_HP{
public:
	PhysicsList(G4int ver = 1);

protected:
	virtual void ConstructProcess() override;
};
