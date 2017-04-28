#pragma once

#define GLM_FORCE_RADIANS

#include <stdio.h>
#include <tchar.h>
#include <gl_core_4_3.hpp>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>

#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include <string.h>
#include <vector>
#include <memory>
#include <map>

#include <LuaBridge.h>
#include <iostream>

extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}

#include "Scene.h"
#include "Destroyable.h"

#include "MessageHandler.h"