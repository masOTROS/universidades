#pragma once
#include "ofMain.h"
#include "ofxCsv.h"

class Data{
public:
    class Rama;
    class Provincia;
    class Universidad;
    
    class Rama{
    public:
        string nombre;
        vector<Provincia *> provincias;
        vector<Universidad *> universidades;
    };
    vector<Rama> Ramas;
    
    class Provincia{
    public:
        string nombre;
        vector<Rama *> ramas;
        vector<Universidad *> universidades;
    };
    vector<Provincia> Provincias;
    
    class Universidad{
    public:
        string nombre;
        vector<Rama *> ramas;
        vector<Provincia *> provincias;
    };
    vector<Universidad> Universidades;
    
    vector<Rama *> filteredRamas;
    vector<Provincia *> filteredProvincias;
    vector<Universidad *> filteredUniversidades;
    
    ofxCsv csv;
    
    void setup();
    void resetFiltered();
    void applyRamaFilter(Rama * r);
    void applyProvinciaFilter(Provincia * p);
    void applyUniversidadFilter(Universidad * u);
    
    bool ramaFilterApplied,provinciaFilterApplied,universidadFilterApplied;
    
    void printFiltered();
};