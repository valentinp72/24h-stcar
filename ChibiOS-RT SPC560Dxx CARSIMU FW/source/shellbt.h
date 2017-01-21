/*
 * Licensed under ST Liberty SW License Agreement V2, (the "License");
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 *        http://www.st.com/software_license_agreement_liberty_v2
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * Size of the stack used by the shell thread.
 */
#define SHELL_WA_SIZE   THD_WA_SIZE(1024)

/*
 * Array of the custom shell commands.
 */
extern const ShellCommand shell_commands[];
extern const ShellCommand shell_commands_car[];
extern Thread *tpgps;
extern bool_t bGpsRunning;
extern WORKING_AREA(waThreadGPS, 128);

msg_t ThreadGPS(void *arg);
