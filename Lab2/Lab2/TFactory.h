#pragma once
#include "TAssessBar.h"
#include "TProgressBar.h"
#include "TButton.h"
#include "TChoice.h"
#include "TInput.h"

class TFactory
{
public:
    virtual TObject* create() = 0;
    virtual ~TFactory();
};

class TAssessFactory : public TFactory
{
public:
    TObject* create();
};

class TProgressFactory : public TFactory
{
public:
    TObject* create();
};

class TChoiceFactory : public TFactory
{
public:
    TObject* create();
};

class TButtonFactory : public TFactory
{
public:
    TObject* create();
};

class TInputFactory : public TFactory
{
public:
    TObject* create();
};

