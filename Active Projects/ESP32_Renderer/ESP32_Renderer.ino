#include <cmath>
#include <LinkedList.h>
#include <Arduino.h>

struct Vector2 { float x,y; };

TaskHandle_t TaskCore0;
LinkedList<Vector2> RenderPipelineA;
LinkedList<Vector2> RenderPipelineB;
bool PipelineSelector = false;





float getDistance(Vector2 point1, Vector2 point2) {
  return sqrt(
    pow(point1.x - point2.x, 2) +
    pow(point1.y - point2.y, 2)
  );
}

LinkedList<Vector2> createLineDefinition(Vector2 pointA, Vector2 pointB, int dotsBudget) {
  LinkedList<Vector2> result = LinkedList<Vector2>();
  for(int i = 0; i < dotsBudget; i++) {
    Vector2 point;
    float perc = float(i)/float(dotsBudget-1);

    point.x = pointA.x + (pointB.x-pointA.x)*perc;
    point.y = pointA.y + (pointB.y-pointA.y)*perc;

    result.add(point);
  }
  
  return result;
}

LinkedList<Vector2> createShape(LinkedList<Vector2> points, int dotsBudget) {
  float perimeter = 0;
  for (int i = 0; i < points.size()-1; i++) {
    perimeter += getDistance(points[i], points[i+1]);
  }

  LinkedList<Vector2> result = LinkedList<Vector2>();
  int dotsUsedTotal = 0;
  for (int i = 1; i < points.size(); i++) {
    int dotsAllowed = dotsBudget * (getDistance(points[i], points[i-1])/perimeter);
    dotsUsedTotal += dotsAllowed;

    LinkedList<Vector2> tmp = createLineDefinition(points[i-1],points[i],dotsAllowed);
    for (int x = 0; x < tmp.size(); x++) {
      result.add(tmp[i]);
    }
  }

  // Dot corrector
  for(int i = 0; i < dotsBudget - dotsUsedTotal; i++) {
    result.add(result.get(result.size() - 1));
  }

  return result;
}

void swapBuffers() {
  PipelineSelector = !PipelineSelector;
  if (PipelineSelector) {
    RenderPipelineA.clear();
  } else {
    RenderPipelineB.clear();
  }
}
void addDataToCurrentBuffer(LinkedList<Vector2> points) {
  for (int i = 0; i < points.size(); i++) {
    if (PipelineSelector) {
      RenderPipelineA.add(points[i]);
    } else {
      RenderPipelineB.add(points[i]);
    }
  }
}

void RenderingEngine(void *parameter) {
  if (PipelineSelector) {
    // Read from RenderPipelineB
  } else {
    // Read from RenderPipelineA
  }
}
void Core0Renderer(void *parameter) {while (true) {RenderingEngine(parameter);}}
























void setup() {
  Serial.begin(115200);

  xTaskCreatePinnedToCore(
    Core0Renderer,     // Function to execute on Core 0
    "TaskCore0",   // Task name
    10000,         // Stack size (bytes)
    NULL,          // Parameters to pass to task (if any)
    1,             // Priority (0 is lowest)
    &TaskCore0,    // Task handle
    0              // Core to run the task on (0 or 1)
  );
}

void loop() {
  // Do game physics

}
