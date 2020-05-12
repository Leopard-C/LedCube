#include "driver/cube.h"
#include "driver/cube_extend.h"
#include "driver/script.h"
#include "utility/image_lib.h"
#include "utility/utils.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <thread>
#include <chrono>
#include <iostream>
#include <fstream>
#include <wiringPi.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>

/**********************************************
 *
 *   Effects
 *
**********************************************/
#include "effect/layer_scan.h"
#include "effect/random_light.h"
#include "effect/layer_scan.h"
#include "effect/drop_line.h"
#include "effect/drop_point.h"
#include "effect/random_drop_point.h"
#include "effect/drop_text_point.h"
#include "effect/text_scan.h"
#include "effect/cube_size_from_vertex.h"
#include "effect/cube_size_from_inner.h"
#include "effect/rise_and_fall/mode_1.h"
#include "effect/rise_and_fall/mode_2.h"
#include "effect/rise_and_fall/mode_3.h"
#include "effect/rise_and_fall/mode_4.h"
#include "effect/rise_and_fall/mode_5.h"
#include "effect/rise_and_fall/mode_6.h"
#include "effect/snake.h"
#include "effect/random_height.h"
#include "effect/fireworks_from_center.h"
#include "effect/wander_edge.h"

LedCube cube;

void sleepMs(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void printUsage() {
    printf("Usage: \n");
    printf("  ./led_cube run [effect_description_file]\n");
    printf("  ./led_cube off\n");
}

void catchCtrlC(int) {
    printf("\nCatch Ctrl+C!\n");
    LedCube::quit();
    exit(1);
}

int run(const char* effectDescFile);


int main(int argc, char** argv) {
    if (argc < 2) {
        printUsage();
        return 1;
    }

    if (wiringPiSetupGpio() == -1) {
        printf("Wiringpi setup failed\n");
        return 1;
    }

    srand(time(NULL));
    signal(SIGINT, catchCtrlC);

    // must setup after wiringPiSetupGpio() !
    cube.setup();

    if (strcmp(argv[1], "run" ) == 0) {
        if (argc != 3) {
            printUsage();
            return 1;
        }
        else {
            return run(argv[2]);
        }
    }
    else if (strcmp(argv[1], "off") == 0) {
        Call(cube.clear());
        return 0;
    }
    else {
        return 1;
    }
}


int run(const char* effectDescFile) {
    // 1. remove annotation
    std::ifstream ifs(effectDescFile);
    if (!ifs.is_open())
        return 1;

    struct timespec tn;
    clock_gettime(CLOCK_REALTIME, &tn);

    char cacheFile[32] = { 0 };
    sprintf(cacheFile, "%d", tn.tv_nsec);

    std::ofstream ofs(cacheFile);
    if (!ofs.is_open()) {
        ifs.close();
        return 1;
    }

    std::string line;
    bool isCommenting = false;
    while (getline(ifs, line)) {
        util::trim(line);
        if (line.empty())
            continue;
        if (isCommenting) {
            if (line == "<END_COMMENT>")
                isCommenting = false;
            continue;
        }
        if (line == "<COMMENT>")
            isCommenting = true;
        else if (line == "<END><END>") {
            ofs << line << std::endl;
            break;
        }
        else if (line.substr(0, 2) != "<#") {
            ofs << line << std::endl;
        }
    }
    ifs.close();
    ofs.close();

    // 2. parse file
    FILE* fp = fopen(cacheFile, "r");
    if (!fp)
        return 1;

    bool ret = 0;

    do {
        while (!feof(fp)) {
            char tag[32] = { 0 };     
            fscanf(fp, "%s", tag);
            util::toUpperCase(tag, strlen(tag));
            if (strcmp(tag, "<CUBESIZEFROMVERTEX>") == 0) {
                CubeSizeFromVertexEffect cubeSizeFromVertex;
                if (cubeSizeFromVertex.readFromFP(fp))
                    cubeSizeFromVertex.showOnce();
                else {
                    ret = 1;
                    break;
                }
            }

            else if (strcmp(tag, "<CUBESIZEFROMINNER>") == 0) { CubeSizeFromInnerEffect cubeSizeFromInner; if (cubeSizeFromInner.readFromFP(fp))
                    cubeSizeFromInner.showOnce();
                else {
                    ret = 1;
                    break;
                }
            }

            else if (strcmp(tag, "<DROPLINE>") == 0) {
                DropLineEffect dropLine;
                if (dropLine.readFromFP(fp))
                    dropLine.showOnce();
                else {
                    ret = 1;
                    break;
                }
            }

            else if (strcmp(tag, "<DROPPOINT>") == 0) {
                DropPointEffect dropPoint;
                if (dropPoint.readFromFP(fp))
                    dropPoint.showOnce();
                else {
                    ret = 1;
                    break;
                }
            }

            else if (strcmp(tag, "<DROPTEXTPOINT>") == 0) {
                DropTextPointEffect dropTextPoint;
                if (dropTextPoint.readFromFP(fp))
                    dropTextPoint.showOnce();
                else {
                    ret = 1;
                    break;
                }
            }

            else if (strcmp(tag, "<LAYERSCAN>") == 0) {
                LayerScanEffect layerScan;
                if (layerScan.readFromFP(fp))
                    layerScan.showOnce();
                else {
                    ret = 1;
                    break;
                }
            }

            else if (strcmp(tag, "<RANDOMDROPPOINT>") == 0) {
                RandomDropPointEffect randomDropPoint;
                if (randomDropPoint.readFromFP(fp))
                    randomDropPoint.showOnce();
                else {
                    ret = 1;
                    break;
                }
            }

            else if (strcmp(tag, "<RANDOMLIGHT>") == 0) {
                RandomLightEffect randomLight;
                if (randomLight.readFromFP(fp))
                    randomLight.showOnce();
                else {
                    ret = 1;
                    break;
                }
            }

            else if (strcmp(tag, "<TEXTSCAN>") == 0) {
                TextScanEffect textScan;
                if (textScan.readFromFP(fp))
                    textScan.showOnce();
                else {
                    ret = 1;
                    break;
                }
            }

            else if (strcmp(tag, "<SNAKE>") == 0) {
                SnakeEffect snake;
                if (snake.readFromFP(fp))
                    snake.showOnce();
                else {
                    ret = 1;
                    break;
                }
            }

            else if (strcmp(tag, "<RANDOMHEIGHT>") == 0) {
                RandomHeightEffect randomHeight;
                if (randomHeight.readFromFP(fp))
                    randomHeight.showOnce();
                else {
                    ret = 1;
                    break;
                }
            }

            else if (strcmp(tag, "<FIREWORKSFROMCENTER>") == 0) {
                FireworksFromCenterEffect fireworksFromCenter;
                if (fireworksFromCenter.readFromFP(fp))
                    fireworksFromCenter.showOnce();
                else {
                    ret = 1;
                    break;
                }
            }

            else if (strcmp(tag, "<RISEANDFALLMODE1>") == 0) {
                RiseAndFallMode1Effect riseAndFallMode1;
                if (riseAndFallMode1.readFromFP(fp))
                    riseAndFallMode1.showOnce();
                else {
                    ret = 1;
                    break;
                }
            }

            else if (strcmp(tag, "<RISEANDFALLMODE2>") == 0) {
                RiseAndFallMode2Effect riseAndFallMode2;
                if (riseAndFallMode2.readFromFP(fp))
                    riseAndFallMode2.showOnce();
                else {
                    ret = 1;
                    break;
                }
            }

            else if (strcmp(tag, "<RISEANDFALLMODE3>") == 0) {
                RiseAndFallMode3Effect riseAndFallMode3;
                if (riseAndFallMode3.readFromFP(fp))
                    riseAndFallMode3.showOnce();
                else {
                    ret = 1;
                    break;
                }
            }

            else if (strcmp(tag, "<RISEANDFALLMODE4>") == 0) {
                RiseAndFallMode4Effect riseAndFallMode4;
                if (riseAndFallMode4.readFromFP(fp))
                    riseAndFallMode4.showOnce();
                else {
                    ret = 1;
                    break;
                }
            }

            else if (strcmp(tag, "<RISEANDFALLMODE5>") == 0) {
                RiseAndFallMode5Effect riseAndFallMode5;
                if (riseAndFallMode5.readFromFP(fp))
                    riseAndFallMode5.showOnce();
                else {
                    ret = 1;
                    break;
                }
            }

            else if (strcmp(tag, "<RISEANDFALLMODE6>") == 0) {
                RiseAndFallMode6Effect riseAndFallMode6;
                if (riseAndFallMode6.readFromFP(fp))
                    riseAndFallMode6.showOnce();
                else {
                    ret = 1;
                    break;
                }
            }

            else if (strcmp(tag, "<WANDEREDGE>") == 0) {
                WanderEdgeEffect wanderEdge;
                if (wanderEdge.readFromFP(fp))
                    wanderEdge.showOnce();
                else {
                    ret = 1;
                    break;
                }
            }


            else if (strcmp(tag, "<SCRIPT>") == 0) {
                bool bBreak = false;;
                while (true) {
                    char tag1[32] = { 0 };
                    fscanf(fp, "%s", tag1);
                    util::toUpperCase(tag1, strlen(tag1));
                    if (strcmp(tag1, "<FILE>") == 0) {
                        char filename[64] = { 0 };
                        fscanf(fp, "%s", filename);
                        Script script;
                        script.run(filename);
                    }
                    else if (strcmp(tag1, "<END>") == 0) {
                        break;
                    }
                    else {
                        bBreak = true;
                        break;
                    }
                }
                if (bBreak) {
                    ret = 1;
                    break;
                }
            }

            else if (strcmp(tag, "<EML>") == 0) {
                bool bBreak = false;;
                while (true) {
                    char tag1[32] = { 0 };
                    fscanf(fp, "%s", tag1);
                    util::toUpperCase(tag1, strlen(tag1));
                    if (strcmp(tag1, "<FILE>") == 0) {
                        char filename[256] = { 0 };
                        fscanf(fp, "%s", filename);
                        if (run(filename) != 0) {
                            bBreak = true;
                            break;
                        }
                    }
                    else if (strcmp(tag1, "<END>") == 0) {
                        break;
                    }
                    else {
                        bBreak = true;
                        break;
                    }
                }
                if (bBreak) {
                    ret = 1;
                    break;
                }
            }

            else if (strcmp(tag, "<END><END>") == 0) {
                ret = 0;
                break;
            }

            else if (strcmp(tag, "") == 0) {
                printf("[Warning] missing <END><END> in the end of the eml-file.\n");
                ret = 0;
                break;
            }

            else {
                ret = 1;
                printf("Unknown tag: %s\n", tag);
                break;
            }
        }
    } while(false);

    fclose(fp);
    remove(cacheFile);
    return ret;
}


