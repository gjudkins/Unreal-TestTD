// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Touchable.generated.h"

/* must have BlueprintType as a specifier to have this interface exposed to blueprints
with this line you can easily add this interface to any blueprint class */
//UINTERFACE(BlueprintType)

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTouchable : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/**
 * 
 */
class TESTTD_API ITouchable
{
	GENERATED_IINTERFACE_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	// putting '= 0' makes it so classes that implement this interface MUST implement this method
	virtual void didSelect() = 0;

	virtual void touchDown() {};

	virtual void touchUp() { didSelect(); };
};
