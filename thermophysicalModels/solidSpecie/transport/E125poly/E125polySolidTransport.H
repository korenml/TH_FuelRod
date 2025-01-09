/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2017 OpenFOAM Foundation
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
    Foam::E125polySolidTransport

Description
    Exponential properties for solid heat transport
    Templated into a given thermodynamics package.

SourceFiles
    E125polySolidTransportI.H
    E125polySolidTransport.C

\*---------------------------------------------------------------------------*/

#ifndef E125polySolidTransport_H
#define E125polySolidTransport_H

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// Forward Declarations

template<class Thermo> class E125polySolidTransport;

template<class Thermo>
inline E125polySolidTransport<Thermo> operator*
(
    const scalar,
    const E125polySolidTransport<Thermo>&
);

template<class Thermo>
Ostream& operator<<
(
    Ostream&,
    const E125polySolidTransport<Thermo>&
);


/*---------------------------------------------------------------------------*\
                  Class E125polySolidTransport Declaration
\*---------------------------------------------------------------------------*/

template<class Thermo>
class E125polySolidTransport
:
    public Thermo
{
    // Private Data

        //- Reference temperature
        scalar Tref_;


    // Private Member Functions

        //- Construct from components
        inline E125polySolidTransport
        (
            const Thermo& t,
            const scalar Tref
        );


public:

    // Generated Methods: copy construct, copy assignment


    // Constructors

        //- Construct as named copy
        inline E125polySolidTransport
        (
            const word&,
            const E125polySolidTransport&
        );

        //- Construct from dictionary
        explicit E125polySolidTransport(const dictionary&);

        // Selector from dictionary
        inline static autoPtr<E125polySolidTransport> New
        (
            const dictionary& dict
        );


    // Member Functions

        //- Return the instantiated type name
        static word typeName()
        {
            return "E125poly<" + Thermo::typeName() + '>';
        }

        //- Is the thermal conductivity isotropic
        static const bool isotropic = true;

        //- Thermal conductivity [W/mK]
        inline scalar kappa(const scalar p, const scalar T) const;

        //- Thermal conductivity [W/mK]
        inline vector Kappa(const scalar p, const scalar T) const;

        //- Dynamic viscosity [kg/ms]
        inline scalar mu(const scalar p, const scalar T) const;

        //- Thermal diffusivity of enthalpy [kg/ms]
        inline scalar alphah(const scalar p, const scalar T) const;

        //- Write to Ostream
        void write(Ostream& os) const;


    // Member Operators

        inline void operator+=(const E125polySolidTransport&);


    // Friend Operators

        friend E125polySolidTransport operator* <Thermo>
        (
            const scalar,
            const E125polySolidTransport&
        );


    // IOstream Operators

        friend Ostream& operator<< <Thermo>
        (
            Ostream&,
            const E125polySolidTransport&
        );
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "E125polySolidTransportI.H"

#ifdef NoRepository
    #include "E125polySolidTransport.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
