#include "Root.h"

stack<glm::mat4> Root::ModelviewMatrix = stack<glm::mat4>();
stack<glm::mat4> Root::ProjectionMatrix = stack<glm::mat4>();
stack<glm::mat3> Root::NormalMatrix = stack<glm::mat3>();