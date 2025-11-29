#include "trie_server.h"
#include "Trie.h"        // student's trie
#include "httplib.h"    // single-header HTTP library: https://github.com/yhirose/cpp-httplib

#include <string>
#include <vector>

// Adjust these to taste
static const char* HOST = "0.0.0.0";
static const int   PORT = 8080;

// Helper: safely extract a query parameter, or empty string if missing.
static std::string get_param(const httplib::Request& req, const std::string& name) {
    auto val = req.get_param_value(name.c_str());
    return val;
}

void start_trie_server(Trie& dict) {
    httplib::Server svr;

    // Simple membership lookup: /lookup?q=word
    // Response (plain text):
    //   "FOUND <word>"      if in trie
    //   "NOT_FOUND <word>"  if not in trie
    svr.Get("/lookup", [&dict](const httplib::Request& req, httplib::Response& res) {
        std::string q = get_param(req, "q");
        if (q.empty()) {
            res.status = 400;
            res.set_content("ERROR missing parameter q", "text/plain");
        }

        bool found = dict.contains(q); //TRIE FUNCTION
        std::string body = found ? "FOUND " + q : "NOT_FOUND " + q;

        //OUTPUT COURSE DATA
        //TODO
        if (found == true)
        {
            Course* course_to_print = dict.swapCodeforPtr(q);
            string courseDescription; //from catalog or classes.colorado.edu
            string courseNotes; //from classes.colorado.edu
            string courseTitle; //catalog, etc.
            string regRestricts; 
            string courseHours;
            string skillsLearnt; //from 3. Skills Learnt
            map<string,string> plansNreqs;
            string subject;
            course_to_print->getCourseInfo(courseTitle, courseDescription, courseNotes, subject, regRestricts, plansNreqs, courseHours, skillsLearnt);
            string newline="\n";
            string border="------------------------";
            body.append(newline);
            body.append("COURSE TITLE");
            body.append(newline);
            body.append(courseTitle);
            body.append(newline);
            body.append(border);
            body.append(newline);
            body.append("DESCRIPTION");
            body.append(newline);
            body.append(courseDescription);
            body.append(newline);
            body.append(border);
            body.append(newline);
            body.append("SKILLS LEARNED");
            body.append(newline);
            body.append(skillsLearnt);
            body.append(newline);
            body.append(border);
            body.append(newline);
            body.append("CREDIT HOURS");
            body.append(newline);
            body.append(courseHours);
            body.append(newline);
            body.append(border);
            body.append(newline);
            body.append("CLASS NOTES");
            body.append(newline);           
            body.append(courseNotes);
            body.append(newline);
            body.append(border);
            body.append(newline);
            body.append("REGISTRATION RESTRICTIONS");
            body.append(newline);
            body.append(regRestricts);
            body.append(newline);
            body.append(border);
            body.append(newline);    
            body.append("DEGREE REQUIREMENTS");
            body.append(newline);
            for (auto i  = plansNreqs.begin(); i!= plansNreqs.end(); i++)
            {
                body.append(i->first);
                body.append(": ");
                body.append(i->second);
                body.append(newline);
            }
            body.append(border);
            body.append(border);
        }
        res.set_content(body, "text/plain");
    });


    // OPTIONAL: autocomplete/prefix search endpoint.
    // To enable this, make sure Trie has a suitable method like:
    //   std::vector<std::string> autocomplete(const std::string& prefix,
    //                                         std::size_t max_results) const;
    //
    // Response format (plain text):
    //   - Each suggestion on its own line.
    //   - Empty body if there are no suggestions.
    svr.Get("/autocomplete", [&dict](const httplib::Request& req, httplib::Response& res) {
        std::string prefix = get_param(req, "q");
        if (prefix.empty()) {
            res.status = 400;
            res.set_content("ERROR missing parameter q", "text/plain");
            return;
        }

        std::size_t limit = 20;
        std::string limit_param = get_param(req, "limit");
        if (!limit_param.empty()) {
            try {
                limit = static_cast<std::size_t>(std::stoul(limit_param));
            } catch (...) {
                // keep default
            }
        }

        // If your Trie does not yet support autocomplete, you can
        // comment out the call below and instead just return an empty body.
        auto suggestions = dict.autocomplete(prefix, limit);

        string body="";
        for (const auto& w : suggestions) {
            body += w;
            body += "\n";
        }

        res.set_content(body, "text/plain");
    });

    // Serve static files (HTML/JS/CSS) from ./static
    // Place index.html inside a directory named "static" next to the executable.
    svr.set_mount_point("/", "./static");

    // Start blocking server loop
    svr.listen(HOST, PORT);
}
