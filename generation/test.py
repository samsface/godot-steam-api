import proc
import out
import out_gdscript
import pprint
from il import ILBuilder

def main():
    ilb = ILBuilder()
    ilb.seed()

    db = ilb.build('lib/steam-sdk/public/steam/steam_api.h')

    # Build a smaller type dp of just the stuff we want to bind.
    # Start with the handwritten SteamAPI type
    trimmed_db = { "SteamAPI": db["SteamAPI"] }
    # Then pull out the types required by the ISteamUtils and ISteamUtils
    for d in (ilb.get_dependencies('ISteamUtils') | ilb.get_dependencies('ISteamUserStats')):
        trimmed_db[d] = db[d]

    #pp = pprint.PrettyPrinter(indent=4)
    #pp.pprint(trimmed_db)

    #proc.optimize(db2)

    out.print_db(trimmed_db)
    #out_gdscript.print_db(db2)

    #out_gdscript.print_db(trimmed_db)

if __name__ == "__main__":
    main()
