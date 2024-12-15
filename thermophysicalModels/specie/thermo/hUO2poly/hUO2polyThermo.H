/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2012-2017 OpenFOAM Foundation
    Copyright (C) 2020 OpenCFD Ltd.
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
    Foam::hUO2polyThermo

Group
    grpSpecieThermo

Description
    Poly-function based thermodynamics package templated on EquationOfState.

    In this thermodynamics package the heat capacity is a simple power of
    temperature:
        tau = T/1000;
        MUO2 = 270.03;
        Cp(T) = MUO2*(52.1743 + 87.951*tau - 84.2411*tau^2 + 31.542*tau^3 - 2.6334*tau^4 + 0.71391*tau^-2);

    which is particularly suitable for solids.

SourceFiles
    hUO2polyThermoI.H
    hUO2polyThermo.C

\*---------------------------------------------------------------------------*/

#ifndef hUO2polyThermo_H
#define hUO2polyThermo_H

#include "scalar.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// Forward declaration of friend functions and operators

template<class EquationOfState> class hUO2polyThermo;

template<class EquationOfState>
inline hUO2polyThermo<EquationOfState> operator+
(
    const hUO2polyThermo<EquationOfState>&,
    const hUO2polyThermo<EquationOfState>&
);

template<class EquationOfState>
inline hUO2polyThermo<EquationOfState> operator*
(
    const scalar,
    const hUO2polyThermo<EquationOfState>&
);


template<class EquationOfState>
inline hUO2polyThermo<EquationOfState> operator==
(
    const hUO2polyThermo<EquationOfState>&,
    const hUO2polyThermo<EquationOfState>&
);


template<class EquationOfState>
Ostream& operator<<
(
    Ostream&,
    const hUO2polyThermo<EquationOfState>&
);


/*---------------------------------------------------------------------------*\
                         Class hUO2polyThermo Declaration
\*---------------------------------------------------------------------------*/

template<class EquationOfState>
class hUO2polyThermo
:
    public EquationOfState
{
    // Private data

        scalar Tref_;
        scalar Hf_;


    // Private Member Functions

        //- Check given temperature is within the range of the fitted coeffs
        inline void checkT(const scalar T) const;

        //- Construct from components
        inline hUO2polyThermo
        (
            const EquationOfState& st,
            const scalar Tref,
            const scalar Hf
        );


public:

    // Constructors

        //- Construct from dictionary
        hUO2polyThermo(const dictionary&);

        //- Construct as a named copy
        inline hUO2polyThermo
        (
            const word&,
            const hUO2polyThermo&
        );

         //- Construct and return a clone
        inline autoPtr<hUO2polyThermo> clone() const;

        //- Selector from dictionary
        inline static autoPtr<hUO2polyThermo> New(const dictionary& dict);


    // Member Functions

        //- Return the instantiated type name
        static word typeName()
        {
            return "hUO2poly<" + EquationOfState::typeName() + '>';
        }

        //- Limit temperature to be within the range
        inline scalar limit(const scalar T) const;


        // Fundamental properties

            //- Heat capacity at constant pressure [J/(kg K)]
            inline scalar Cp(const scalar p, const scalar T) const;

            //- Absolute Enthalpy [J/kg]
            inline scalar Ha(const scalar p, const scalar T) const;

            //- Sensible enthalpy [J/kg]
            inline scalar Hs(const scalar p, const scalar T) const;

            //- Chemical enthalpy [J/kg]
            inline scalar Hc() const;

            //- Entropy [J/(kg K)]
            inline scalar S(const scalar p, const scalar T) const;

            //- Gibbs free energy of the mixture in the standard state [J/kg]
            inline scalar Gstd(const scalar T) const;


            #include "HtoEthermo.H"


        // Derivative term used for Jacobian


            //- Temperature derivative of heat capacity at constant pressure
            inline scalar dCpdT(const scalar p, const scalar T) const;



    // Member operators

        inline void operator+=(const hUO2polyThermo&);


    // Friend operators

        friend hUO2polyThermo operator+ <EquationOfState>
        (
            const hUO2polyThermo&,
            const hUO2polyThermo&
        );

        friend hUO2polyThermo operator* <EquationOfState>
        (
            const scalar,
            const hUO2polyThermo&
        );


        friend hUO2polyThermo operator== <EquationOfState>
        (
            const hUO2polyThermo&,
            const hUO2polyThermo&
        );


    // Ostream Operator

        friend Ostream& operator<< <EquationOfState>
        (
            Ostream&,
            const hUO2polyThermo&
        );
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
    #include "hUO2polyThermoI.H"
    #include "hUO2polyThermo.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
