void ERR__raiseError(const char* file, const char* function, const char* note)
{
    Serial.println();

    Serial.print("[ERROR] ");
    Serial.println(file);
    Serial.print("   > ");
    Serial.print(function);
    Serial.print(" > ");
    Serial.println(note);

    while(1);
}

void ERR__raiseWarning(const char* file, const char* function, const char* note)
{
    Serial.println();

    Serial.print("[WARNING] ");
    Serial.println(file);
    Serial.print("   > ");
    Serial.print(function);
    Serial.print(" > ");
    Serial.println(note);

    while(1);
}