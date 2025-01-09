/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2017 OpenFOAM Foundation
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

\*---------------------------------------------------------------------------*/

#include "mathematicalConstants.H"

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Thermo>
inline Foam::E125polySolidTransport<Thermo>::E125polySolidTransport
(
    const Thermo& t,
    const scalar Tref
)
:
    Thermo(t),
    Tref_(Tref)
{}


template<class Thermo>
inline Foam::E125polySolidTransport<Thermo>::E125polySolidTransport
(
    const word& name,
    const E125polySolidTransport& ct
)
:
    Thermo(name, ct),
    Tref_(ct.Tref_)
{}


template<class Thermo>
inline Foam::autoPtr<Foam::E125polySolidTransport<Thermo>>
Foam::E125polySolidTransport<Thermo>::New
(
    const dictionary& dict
)
{
    return autoPtr<E125polySolidTransport<Thermo>>::New(dict);
}

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Thermo>
inline Foam::scalar Foam::E125polySolidTransport<Thermo>::kappa
(
    const scalar p, const scalar T
) const
{
	if (T < 300)
	{
		const scalar kappa = 17.5;
	}
	else if(T >= 300 && T <= 1100)
	{
    	const scalar kappa = 14.0 + 0.0115*T;
    }
    else
    {
    	const scalar kappa = 27.0;
    }
    return kappa;
}


template<class Thermo>
inline Foam::vector Foam::E125polySolidTransport<Thermo>::Kappa
(
    const scalar p, const scalar T
) const
{
	if (T < 300)
	{
		const scalar kappa = 17.5;
	}
	else if(T >= 300 && T <= 1100)
	{
    	const scalar kappa = 14.0 + 0.0115*T;
    }
    else
    {
    	const scalar kappa = 27.0;
    }
    return vector(kappa, kappa, kappa);
}


template<class Thermo>
inline Foam::scalar Foam::E125polySolidTransport<Thermo>::
mu(const scalar p, const scalar T) const
{
    NotImplemented;
    return 0;
}


template<class Thermo>
inline Foam::scalar Foam::E125polySolidTransport<Thermo>::
alphah(const scalar p, const scalar T) const
{
    return kappa(p, T)/this->Cp(p, T);
}

// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class Thermo>
inline void Foam::E125polySolidTransport<Thermo>::operator+=
(
    const E125polySolidTransport<Thermo>& ct
)
{
    scalar Y1 = this->Y();

    Y1 /= this->Y();
    scalar Y2 = ct.Y()/this->Y();

    Tref_ = (Y1*Tref_ + Y2*ct.Tref_);
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

template<class Thermo>
inline Foam::E125polySolidTransport<Thermo> Foam::operator*
(
    const scalar s,
    const E125polySolidTransport<Thermo>& ct
)
{
    return E125polySolidTransport<Thermo>
    (
        s*static_cast<const Thermo&>(ct),
        ct.Tref_
    );
}

// ************************************************************************* //
