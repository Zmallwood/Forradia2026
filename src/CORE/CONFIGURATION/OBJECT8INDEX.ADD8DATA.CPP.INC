ADD8ENTRY("ObjectStone", "Stone", OBJECT8FLAGS::kSmallObject);

ADD8ENTRY("ObjectBranch", "Branch", OBJECT8FLAGS::kSmallObject);

ADD8ENTRY("ObjectPinkFlower", "Pink flower", OBJECT8FLAGS::kSmallObject);

ADD8ENTRY("ObjectLeaf", "Leaf", OBJECT8FLAGS::kSmallObject);

ADD8ENTRY("ObjectPoolOfBlood", "Pool of blood", OBJECT8FLAGS::kSmallObject);

auto allImpactPointsCompletedActionObjectTree1{
    [](std::shared_ptr<OBJECT> object) {
        auto worldArea{_<WORLD>().currentWorldArea_};

        auto facedTileCoordinate{_<PLAYER>().facedTileCoordinate_};

        auto facedTile{worldArea->GET8TILE(facedTileCoordinate)};

        facedTile->tileObjects_->TRANSFORM8OBJECT(object, "ObjectFelledTree");

        _<GUI8TEXT8CONSOLE>().PRINT8LINE("You have felled the tree.");

        _<PLAYER>().ADD8EXPERIENCE(13);
    }};

ADD8ENTRY("ObjectTree1", "Tree",
          OBJECT8FLAGS::kBlocksSight | OBJECT8FLAGS::kUnmovable,
          {POINT8F{0.5f, 0.95f}, POINT8F{0.55f, 0.95f}, POINT8F{0.6f, 0.95f}},
          {{"ObjectWoodAxe", []() {},
            allImpactPointsCompletedActionObjectTree1}});

auto allImpactPointsCompletedActionObjectTree2{
    allImpactPointsCompletedActionObjectTree1};

ADD8ENTRY("ObjectTree2", "Tree",
          OBJECT8FLAGS::kBlocksSight | OBJECT8FLAGS::kUnmovable,
          {POINT8F{0.5f, 0.8f}, POINT8F{0.53f, 0.8f}, POINT8F{0.56f, 0.8f}},
          {{"ObjectWoodAxe", []() {},
            allImpactPointsCompletedActionObjectTree2}});

ADD8ENTRY("ObjectBush1", "Bush",
          OBJECT8FLAGS::kBlocksSight | OBJECT8FLAGS::kUnmovable);

ADD8ENTRY("ObjectStoneBoulder", "Stone boulder",
          OBJECT8FLAGS::kBlocksSight | OBJECT8FLAGS::kUnmovable, {},
          {{"", []() {}, [](std::shared_ptr<OBJECT>) {}}}, "",
          POINT8F{0.0f, 0.3f}, POINT8F{0.0f, 0.0f});

ADD8ENTRY("ObjectCreatureDeerCorpse", "Deer corpse", 0);

ADD8ENTRY("ObjectCreatureBoarCorpse", "Boar corpse", 0);

ADD8ENTRY("ObjectRedApple", "Red apple", OBJECT8FLAGS::kSmallObject);

ADD8ENTRY("ObjectCopperSword", "Copper sword", OBJECT8FLAGS::kSmallObject);

ADD8ENTRY("ObjectWoodAxe", "Wood axe", OBJECT8FLAGS::kSmallObject);

auto singleImpactPointCompletedActionObjectFelledTree{[]() {
    auto worldArea{_<WORLD>().currentWorldArea_};

    auto facedTileCoordinate{_<PLAYER>().facedTileCoordinate_};

    auto facedTile{worldArea->GET8TILE(facedTileCoordinate)};

    facedTile->tileObjects_->ADD8OBJECT("ObjectWoodLog");

    _<GUI8TEXT8CONSOLE>().PRINT8LINE("You have chopped some wood logs.");

    _<PLAYER>().ADD8EXPERIENCE(7);
}};

auto allImpactPointsCompletedActionObjectFelledTree{
    [](std::shared_ptr<OBJECT> object) {
        auto worldArea{_<WORLD>().currentWorldArea_};

        auto facedTileCoordinate{_<PLAYER>().facedTileCoordinate_};

        auto facedTile{worldArea->GET8TILE(facedTileCoordinate)};

        facedTile->tileObjects_->REMOVE8OBJECT(object);

        _<GUI8TEXT8CONSOLE>().PRINT8LINE(
            "You have chopped up the felled tree.");
    }};

ADD8ENTRY("ObjectFelledTree", "Felled tree", OBJECT8FLAGS::kUnmovable,
          {POINT8F{0.55f, 0.95f}, POINT8F{0.55f, 0.89f}, POINT8F{0.55f, 0.83f},
           POINT8F{0.55f, 0.77f}},
          {{"ObjectWoodAxe", singleImpactPointCompletedActionObjectFelledTree,
            allImpactPointsCompletedActionObjectFelledTree}});

auto allImpactPointsCompletedActionObjectWoodLogUsingSaw{
    [](std::shared_ptr<OBJECT> object) {
        auto worldArea{_<WORLD>().currentWorldArea_};

        auto facedTileCoordinate{_<PLAYER>().facedTileCoordinate_};

        auto facedTile{worldArea->GET8TILE(facedTileCoordinate)};

        facedTile->tileObjects_->TRANSFORM8OBJECT(object, "ObjectWoodPlank");

        _<GUI8TEXT8CONSOLE>().PRINT8LINE("You have sawed the wood log.");
    }};

auto allImpactPointsCompletedActionObjectWoodLogUsingWoodAxe{
    [](std::shared_ptr<OBJECT> object) {
        auto worldArea{_<WORLD>().currentWorldArea_};

        auto facedTileCoordinate{_<PLAYER>().facedTileCoordinate_};

        auto facedTile{worldArea->GET8TILE(facedTileCoordinate)};

        facedTile->tileObjects_->TRANSFORM8OBJECT(object,
                                                  "ObjectUnlitCampfire");

        _<GUI8TEXT8CONSOLE>().PRINT8LINE("You have created a campfire.");

        _<PLAYER>().ADD8EXPERIENCE(13);
    }};

ADD8ENTRY("ObjectWoodLog", "Wood log", OBJECT8FLAGS::kSmallObject,
          {POINT8F{0.5f, 0.93f}},
          {{"ObjectSaw", []() {},
            allImpactPointsCompletedActionObjectWoodLogUsingSaw},
           {"ObjectWoodAxe", []() {},
            allImpactPointsCompletedActionObjectWoodLogUsingWoodAxe}});

ADD8ENTRY("ObjectUnlitCampfire", "Unlit campfire");

ADD8ENTRY("ObjectFlintAndSteel", "Flint and steel", OBJECT8FLAGS::kSmallObject);

ADD8ENTRY("ObjectWoodPlank", "Wood plank", OBJECT8FLAGS::kSmallObject);

ADD8ENTRY("ObjectSaw", "Saw", OBJECT8FLAGS::kSmallObject);

ADD8ENTRY("ObjectHammer", "Hammer", OBJECT8FLAGS::kSmallObject);

auto allImpactPointsCompletedActionObjectWoodWallPlankNorth1{
    [](std::shared_ptr<OBJECT> object) {
        auto worldArea{_<WORLD>().currentWorldArea_};

        auto facedTileCoordinate{_<PLAYER>().facedTileCoordinate_};

        auto facedTile{worldArea->GET8TILE(facedTileCoordinate)};

        facedTile->tileObjects_->TRANSFORM8OBJECT(object,
                                                  "ObjectWoodWallPlankNorth1");
    }};

ADD8ENTRY("ObjectPlannedWoodWallNorthPlank1",
          "Planned wood wall north, plank 1", OBJECT8FLAGS::kUnmovable,
          {POINT8F{0.5f, 0.08f}, POINT8F{0.5f, 0.92f}},
          {{"ObjectHammer", []() {},
            allImpactPointsCompletedActionObjectWoodWallPlankNorth1}},
          "ObjectPlannedObject");

auto allImpactPointsCompletedActionObjectWoodWallPlankNorth2{
    [](std::shared_ptr<OBJECT> object) {
        auto worldArea{_<WORLD>().currentWorldArea_};

        auto facedTileCoordinate{_<PLAYER>().facedTileCoordinate_};

        auto facedTile{worldArea->GET8TILE(facedTileCoordinate)};

        facedTile->tileObjects_->TRANSFORM8OBJECT(object,
                                                  "ObjectWoodWallPlankNorth2");
    }};

ADD8ENTRY("ObjectPlannedWoodWallNorthPlank2",
          "Planned wood wall north, plank 2", OBJECT8FLAGS::kUnmovable,
          {POINT8F{0.5f, 0.08f}, POINT8F{0.5f, 0.92f}},
          {{"ObjectHammer", []() {},
            allImpactPointsCompletedActionObjectWoodWallPlankNorth2}},
          "ObjectPlannedObject");

auto allImpactPointsCompletedActionObjectWoodWallPlankNorth3{
    [](std::shared_ptr<OBJECT> object) {
        auto worldArea{_<WORLD>().currentWorldArea_};

        auto facedTileCoordinate{_<PLAYER>().facedTileCoordinate_};

        auto facedTile{worldArea->GET8TILE(facedTileCoordinate)};

        facedTile->tileObjects_->TRANSFORM8OBJECT(object,
                                                  "ObjectWoodWallPlankNorth3");
    }};

ADD8ENTRY("ObjectPlannedWoodWallNorthPlank3",
          "Planned wood wall north, plank 3", OBJECT8FLAGS::kUnmovable,
          {POINT8F{0.5f, 0.08f}, POINT8F{0.5f, 0.92f}},
          {{"ObjectHammer", []() {},
            allImpactPointsCompletedActionObjectWoodWallPlankNorth3}},
          "ObjectPlannedObject");

auto allImpactPointsCompletedActionObjectWoodWallPlankNorth4{
    [](std::shared_ptr<OBJECT> object) {
        auto worldArea{_<WORLD>().currentWorldArea_};

        auto facedTileCoordinate{_<PLAYER>().facedTileCoordinate_};

        auto facedTile{worldArea->GET8TILE(facedTileCoordinate)};

        facedTile->tileObjects_->TRANSFORM8OBJECT(object,
                                                  "ObjectWoodWallPlankNorth4");
    }};

ADD8ENTRY("ObjectPlannedWoodWallNorthPlank4",
          "Planned wood wall north, plank 1", OBJECT8FLAGS::kUnmovable,
          {POINT8F{0.5f, 0.08f}, POINT8F{0.5f, 0.92f}},
          {{"ObjectHammer", []() {},
            allImpactPointsCompletedActionObjectWoodWallPlankNorth4}},
          "ObjectPlannedObject");

ADD8ENTRY("ObjectWoodWallPlankNorth1", "Wood wall", OBJECT8FLAGS::kUnmovable,
          {}, {{"", []() {}, [](std::shared_ptr<OBJECT>) {}}},
          "ObjectWoodWallPlankNorth1WorldView", POINT8F{0.0f, 0.5f});

ADD8ENTRY("ObjectWoodWallPlankNorth2", "Wood wall", OBJECT8FLAGS::kUnmovable,
          {}, {{"", []() {}, [](std::shared_ptr<OBJECT>) {}}},
          "ObjectWoodWallPlankNorth2WorldView", POINT8F{0.0f, 0.5f});

ADD8ENTRY("ObjectWoodWallPlankNorth3", "Wood wall", OBJECT8FLAGS::kUnmovable,
          {}, {{"", []() {}, [](std::shared_ptr<OBJECT>) {}}},
          "ObjectWoodWallPlankNorth3WorldView", POINT8F{0.0f, 0.5f});

ADD8ENTRY("ObjectWoodWallPlankNorth4", "Wood wall", OBJECT8FLAGS::kUnmovable,
          {}, {{"", []() {}, [](std::shared_ptr<OBJECT>) {}}},
          "ObjectWoodWallPlankNorth4WorldView", POINT8F{0.0f, 0.5f});

auto allImpactPointsCompletedActionObjectWoodWallPlankEast1{
    [](std::shared_ptr<OBJECT> object) {
        auto worldArea{_<WORLD>().currentWorldArea_};

        auto facedTileCoordinate{_<PLAYER>().facedTileCoordinate_};

        auto facedTile{worldArea->GET8TILE(facedTileCoordinate)};

        facedTile->tileObjects_->TRANSFORM8OBJECT(object,
                                                  "ObjectWoodWallPlankEast1");
    }};

ADD8ENTRY("ObjectPlannedWoodWallEastPlank1", "Planned wood wall east, plank 1",
          OBJECT8FLAGS::kUnmovable,
          {POINT8F{0.5f, 0.08f}, POINT8F{0.5f, 0.92f}},
          {{"ObjectHammer", []() {},
            allImpactPointsCompletedActionObjectWoodWallPlankEast1}},
          "ObjectPlannedObject");

auto allImpactPointsCompletedActionObjectWoodWallPlankEast2{
    [](std::shared_ptr<OBJECT> object) {
        auto worldArea{_<WORLD>().currentWorldArea_};

        auto facedTileCoordinate{_<PLAYER>().facedTileCoordinate_};

        auto facedTile{worldArea->GET8TILE(facedTileCoordinate)};

        facedTile->tileObjects_->TRANSFORM8OBJECT(object,
                                                  "ObjectWoodWallPlankEast2");
    }};

ADD8ENTRY("ObjectPlannedWoodWallEastPlank2", "Planned wood wall east, plank 2",
          OBJECT8FLAGS::kUnmovable,
          {POINT8F{0.5f, 0.08f}, POINT8F{0.5f, 0.92f}},
          {{"ObjectHammer", []() {},
            allImpactPointsCompletedActionObjectWoodWallPlankEast2}},
          "ObjectPlannedObject");

auto allImpactPointsCompletedActionObjectWoodWallPlankEast3{
    [](std::shared_ptr<OBJECT> object) {
        auto worldArea{_<WORLD>().currentWorldArea_};

        auto facedTileCoordinate{_<PLAYER>().facedTileCoordinate_};

        auto facedTile{worldArea->GET8TILE(facedTileCoordinate)};

        facedTile->tileObjects_->TRANSFORM8OBJECT(object,
                                                  "ObjectWoodWallPlankEast3");
    }};

ADD8ENTRY("ObjectPlannedWoodWallEastPlank3", "Planned wood wall east, plank 3",
          OBJECT8FLAGS::kUnmovable,
          {POINT8F{0.5f, 0.08f}, POINT8F{0.5f, 0.92f}},
          {{"ObjectHammer", []() {},
            allImpactPointsCompletedActionObjectWoodWallPlankEast3}},
          "ObjectPlannedObject");

auto allImpactPointsCompletedActionObjectWoodWallPlankEast4{
    [](std::shared_ptr<OBJECT> object) {
        auto worldArea{_<WORLD>().currentWorldArea_};

        auto facedTileCoordinate{_<PLAYER>().facedTileCoordinate_};

        auto facedTile{worldArea->GET8TILE(facedTileCoordinate)};

        facedTile->tileObjects_->TRANSFORM8OBJECT(object,
                                                  "ObjectWoodWallPlankEast4");
    }};

ADD8ENTRY("ObjectPlannedWoodWallEastPlank4", "Planned wood wall east, plank 4",
          OBJECT8FLAGS::kUnmovable,
          {POINT8F{0.5f, 0.08f}, POINT8F{0.5f, 0.92f}},
          {{"ObjectHammer", []() {},
            allImpactPointsCompletedActionObjectWoodWallPlankEast4}},
          "ObjectPlannedObject");

ADD8ENTRY("ObjectWoodWallPlankEast1", "Wood wall", OBJECT8FLAGS::kUnmovable, {},
          {{"", []() {}, [](std::shared_ptr<OBJECT>) {}}},
          "ObjectWoodWallPlankEast1WorldView", POINT8F{0.0f, 0.5f});

ADD8ENTRY("ObjectWoodWallPlankEast2", "Wood wall", OBJECT8FLAGS::kUnmovable, {},
          {{"", []() {}, [](std::shared_ptr<OBJECT>) {}}},
          "ObjectWoodWallPlankEast2WorldView", POINT8F{0.0f, 0.5f});

ADD8ENTRY("ObjectWoodWallPlankEast3", "Wood wall", OBJECT8FLAGS::kUnmovable, {},
          {{"", []() {}, [](std::shared_ptr<OBJECT>) {}}},
          "ObjectWoodWallPlankEast3WorldView", POINT8F{0.0f, 0.5f});

ADD8ENTRY("ObjectWoodWallPlankEast4", "Wood wall", OBJECT8FLAGS::kUnmovable, {},
          {{"", []() {}, [](std::shared_ptr<OBJECT>) {}}},
          "ObjectWoodWallPlankEast4WorldView", POINT8F{0.0f, 0.5f});

auto allImpactPointsCompletedActionObjectWoodWallPlankSouth1{
    [](std::shared_ptr<OBJECT> object) {
        auto worldArea{_<WORLD>().currentWorldArea_};

        auto facedTileCoordinate{_<PLAYER>().facedTileCoordinate_};

        auto facedTile{worldArea->GET8TILE(facedTileCoordinate)};

        facedTile->tileObjects_->TRANSFORM8OBJECT(object,
                                                  "ObjectWoodWallPlankSouth1");
    }};

ADD8ENTRY("ObjectPlannedWoodWallSouthPlank1",
          "Planned wood wall south, plank 1", OBJECT8FLAGS::kUnmovable,
          {POINT8F{0.5f, 0.08f}, POINT8F{0.5f, 0.92f}},
          {{"ObjectHammer", []() {},
            allImpactPointsCompletedActionObjectWoodWallPlankSouth1}},
          "ObjectPlannedObject");

auto allImpactPointsCompletedActionObjectWoodWallPlankSouth2{
    [](std::shared_ptr<OBJECT> object) {
        auto worldArea{_<WORLD>().currentWorldArea_};

        auto facedTileCoordinate{_<PLAYER>().facedTileCoordinate_};

        auto facedTile{worldArea->GET8TILE(facedTileCoordinate)};

        facedTile->tileObjects_->TRANSFORM8OBJECT(object,
                                                  "ObjectWoodWallPlankSouth2");
    }};

ADD8ENTRY("ObjectPlannedWoodWallSouthPlank2",
          "Planned wood wall south, plank 2", OBJECT8FLAGS::kUnmovable,
          {POINT8F{0.5f, 0.08f}, POINT8F{0.5f, 0.92f}},
          {{"ObjectHammer", []() {},
            allImpactPointsCompletedActionObjectWoodWallPlankSouth2}},
          "ObjectPlannedObject");

auto allImpactPointsCompletedActionObjectWoodWallPlankSouth3{
    [](std::shared_ptr<OBJECT> object) {
        auto worldArea{_<WORLD>().currentWorldArea_};

        auto facedTileCoordinate{_<PLAYER>().facedTileCoordinate_};

        auto facedTile{worldArea->GET8TILE(facedTileCoordinate)};

        facedTile->tileObjects_->TRANSFORM8OBJECT(object,
                                                  "ObjectWoodWallPlankSouth3");
    }};

ADD8ENTRY("ObjectPlannedWoodWallSouthPlank3",
          "Planned wood wall south, plank 3", OBJECT8FLAGS::kUnmovable,
          {POINT8F{0.5f, 0.08f}, POINT8F{0.5f, 0.92f}},
          {{"ObjectHammer", []() {},
            allImpactPointsCompletedActionObjectWoodWallPlankSouth3}},
          "ObjectPlannedObject");

auto allImpactPointsCompletedActionObjectWoodWallPlankSouth4{
    [](std::shared_ptr<OBJECT> object) {
        auto worldArea{_<WORLD>().currentWorldArea_};

        auto facedTileCoordinate{_<PLAYER>().facedTileCoordinate_};

        auto facedTile{worldArea->GET8TILE(facedTileCoordinate)};

        facedTile->tileObjects_->TRANSFORM8OBJECT(object,
                                                  "ObjectWoodWallPlankSouth4");
    }};

ADD8ENTRY("ObjectPlannedWoodWallSouthPlank4",
          "Planned wood wall south, plank 4", OBJECT8FLAGS::kUnmovable,
          {POINT8F{0.5f, 0.08f}, POINT8F{0.5f, 0.92f}},
          {{"ObjectHammer", []() {},
            allImpactPointsCompletedActionObjectWoodWallPlankSouth4}},
          "ObjectPlannedObject");

ADD8ENTRY("ObjectWoodWallPlankSouth1", "Wood wall", OBJECT8FLAGS::kUnmovable,
          {}, {{"", []() {}, [](std::shared_ptr<OBJECT>) {}}},
          "ObjectWoodWallPlankSouth1WorldView", POINT8F{0.0f, 0.5f});

ADD8ENTRY("ObjectWoodWallPlankSouth2", "Wood wall", OBJECT8FLAGS::kUnmovable,
          {}, {{"", []() {}, [](std::shared_ptr<OBJECT>) {}}},
          "ObjectWoodWallPlankSouth2WorldView", POINT8F{0.0f, 0.5f});

ADD8ENTRY("ObjectWoodWallPlankSouth3", "Wood wall", OBJECT8FLAGS::kUnmovable,
          {}, {{"", []() {}, [](std::shared_ptr<OBJECT>) {}}},
          "ObjectWoodWallPlankSouth3WorldView", POINT8F{0.0f, 0.5f});

ADD8ENTRY("ObjectWoodWallPlankSouth4", "Wood wall", OBJECT8FLAGS::kUnmovable,
          {}, {{"", []() {}, [](std::shared_ptr<OBJECT>) {}}},
          "ObjectWoodWallPlankSouth4WorldView", POINT8F{0.0f, 0.5f});

auto allImpactPointsCompletedActionObjectWoodWallPlankWest1{
    [](std::shared_ptr<OBJECT> object) {
        auto worldArea{_<WORLD>().currentWorldArea_};

        auto facedTileCoordinate{_<PLAYER>().facedTileCoordinate_};

        auto facedTile{worldArea->GET8TILE(facedTileCoordinate)};

        facedTile->tileObjects_->TRANSFORM8OBJECT(object,
                                                  "ObjectWoodWallPlankWest1");
    }};

ADD8ENTRY("ObjectPlannedWoodWallWestPlank1", "Planned wood wall west, plank 1",
          OBJECT8FLAGS::kUnmovable,
          {POINT8F{0.5f, 0.08f}, POINT8F{0.5f, 0.92f}},
          {{"ObjectHammer", []() {},
            allImpactPointsCompletedActionObjectWoodWallPlankWest1}},
          "ObjectPlannedObject");

auto allImpactPointsCompletedActionObjectWoodWallPlankWest2{
    [](std::shared_ptr<OBJECT> object) {
        auto worldArea{_<WORLD>().currentWorldArea_};

        auto facedTileCoordinate{_<PLAYER>().facedTileCoordinate_};

        auto facedTile{worldArea->GET8TILE(facedTileCoordinate)};

        facedTile->tileObjects_->TRANSFORM8OBJECT(object,
                                                  "ObjectWoodWallPlankWest2");
    }};

ADD8ENTRY("ObjectPlannedWoodWallWestPlank2", "Planned wood wall west, plank 2",
          OBJECT8FLAGS::kUnmovable,
          {POINT8F{0.5f, 0.08f}, POINT8F{0.5f, 0.92f}},
          {{"ObjectHammer", []() {},
            allImpactPointsCompletedActionObjectWoodWallPlankWest2}},
          "ObjectPlannedObject");

auto allImpactPointsCompletedActionObjectWoodWallPlankWest3{
    [](std::shared_ptr<OBJECT> object) {
        auto worldArea{_<WORLD>().currentWorldArea_};

        auto facedTileCoordinate{_<PLAYER>().facedTileCoordinate_};

        auto facedTile{worldArea->GET8TILE(facedTileCoordinate)};

        facedTile->tileObjects_->TRANSFORM8OBJECT(object,
                                                  "ObjectWoodWallPlankWest3");
    }};

ADD8ENTRY("ObjectPlannedWoodWallWestPlank3", "Planned wood wall west, plank 3",
          OBJECT8FLAGS::kUnmovable,
          {POINT8F{0.5f, 0.08f}, POINT8F{0.5f, 0.92f}},
          {{"ObjectHammer", []() {},
            allImpactPointsCompletedActionObjectWoodWallPlankWest3}},
          "ObjectPlannedObject");

auto allImpactPointsCompletedActionObjectWoodWallPlankWest4{
    [](std::shared_ptr<OBJECT> object) {
        auto worldArea{_<WORLD>().currentWorldArea_};

        auto facedTileCoordinate{_<PLAYER>().facedTileCoordinate_};

        auto facedTile{worldArea->GET8TILE(facedTileCoordinate)};

        facedTile->tileObjects_->TRANSFORM8OBJECT(object,
                                                  "ObjectWoodWallPlankWest4");
    }};

ADD8ENTRY("ObjectPlannedWoodWallWestPlank4", "Planned wood wall west, plank 4",
          OBJECT8FLAGS::kUnmovable,
          {POINT8F{0.5f, 0.08f}, POINT8F{0.5f, 0.92f}},
          {{"ObjectHammer", []() {},
            allImpactPointsCompletedActionObjectWoodWallPlankWest4}},
          "ObjectPlannedObject");

ADD8ENTRY("ObjectWoodWallPlankWest1", "Wood wall", OBJECT8FLAGS::kUnmovable, {},
          {{"", []() {}, [](std::shared_ptr<OBJECT>) {}}},
          "ObjectWoodWallPlankWest1WorldView", POINT8F{0.0f, 0.5f});

ADD8ENTRY("ObjectWoodWallPlankWest2", "Wood wall", OBJECT8FLAGS::kUnmovable, {},
          {{"", []() {}, [](std::shared_ptr<OBJECT>) {}}},
          "ObjectWoodWallPlankWest2WorldView", POINT8F{0.0f, 0.5f});

ADD8ENTRY("ObjectWoodWallPlankWest3", "Wood wall", OBJECT8FLAGS::kUnmovable, {},
          {{"", []() {}, [](std::shared_ptr<OBJECT>) {}}},
          "ObjectWoodWallPlankWest3WorldView", POINT8F{0.0f, 0.5f});

ADD8ENTRY("ObjectWoodWallPlankWest4", "Wood wall", OBJECT8FLAGS::kUnmovable, {},
          {{"", []() {}, [](std::shared_ptr<OBJECT>) {}}},
          "ObjectWoodWallPlankWest4WorldView", POINT8F{0.0f, 0.5f});

auto allImpactPointsCompletedActionObjectWoodFloor{
    [](std::shared_ptr<OBJECT> object) {
        auto worldArea{_<WORLD>().currentWorldArea_};

        auto facedTileCoordinate{_<PLAYER>().facedTileCoordinate_};

        auto facedTile{worldArea->GET8TILE(facedTileCoordinate)};

        facedTile->tileObjects_->REMOVE8OBJECT(object);

        facedTile->ground_ = HASH("GroundWoodFloor");
    }};

ADD8ENTRY("ObjectPlannedWoodFloor", "Planned wood floor",
          OBJECT8FLAGS::kUnmovable,
          {POINT8F{0.25f, 0.25f}, POINT8F{0.75f, 0.25f}, POINT8F{0.25f, 0.75f},
           POINT8F{0.75f, 0.75f}},
          {{"ObjectHammer", []() {},
            allImpactPointsCompletedActionObjectWoodFloor}},
          "ObjectPlannedObject", POINT8F{0.0f, 0.0f}, POINT8F{0.0f, 0.3f});