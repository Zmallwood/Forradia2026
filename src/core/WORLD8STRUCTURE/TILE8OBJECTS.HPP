//////////////////////////////////////////////////////////////////////////
//                               Forradia                               //
//                                                                      //
// Copyright (c) 2026 Andreas Åkerberg                                  //
// SPDX-License-Identifier: MIT                                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

namespace FORRADIA8GAME
{
    class OBJECT;

    class TILE8OBJECTS
    {
      public:
        void CLEAR();

        void ADD8OBJECT(int objectType, POINT position = {-1, -1});

        void ADD8OBJECT(std::string_view objectName, POINT position = {-1, -1});

        void ADD8OBJECT(std::shared_ptr<OBJECT> object,
                        POINT position = {-1, -1});

        int COUNT();

        void TRANSFORM8OBJECT(std::shared_ptr<OBJECT> object,
                              std::string_view newObjectType);

        std::shared_ptr<OBJECT> PICK8OBJECT(std::shared_ptr<OBJECT> object);

        void REMOVE8OBJECT(std::shared_ptr<OBJECT> object);

        bool HAS8OBJECT8OF8TYPE(std::string_view objectType);

        std::map<POINT, std::shared_ptr<OBJECT>> objects_;
    };
}