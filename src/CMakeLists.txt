set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

# set include dir
include_directories ("${PROJECT_SOURCE_DIR}/include")

# set files used to build
set (PROJECT_SOURCES
      main.cpp
      GameObject.cpp
      Ship.cpp
      Bullet.cpp
      EnemyShip.cpp
      Utils.cpp
      Collision.cpp
      Explosion.cpp
      TextureManager.cpp
      Highscore.cpp
      StateManager.cpp
      LivePowerUp.cpp
      Game.cpp
    )

set (PROJECT_LIB_SOURCES
      GameObject.cpp
      Ship.cpp
      Bullet.cpp
      EnemyShip.cpp
      Utils.cpp
      Collision.cpp
      Explosion.cpp
      TextureManager.cpp
      Highscore.cpp
      StateManager.cpp
      LivePowerUp.cpp
      Game.cpp
    )

set (PROJECT_HEADERS
      ../include/GameObject.h
      ../include/Ship.h
      ../include/Bullet.h
      ../include/EnemyShip.h
      ../include/Utils.h
      ../include/Collision.h
      ../include/Explosion.h
      ../include/TextureManager.h
      ../include/Highscore.h
      ../include/GameState.h
      ../include/StateManager.h
      ../include/LivePowerUp.h
      ../include/Game.h
    )

# create executable
add_executable (asteroids ${PROJECT_SOURCES})
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(asteroids ${SFML_LIBRARIES})
endif()

# create library target
add_library (Asteroids ${PROJECT_LIB_SOURCES} ${PROJECT_HEADERS})
