#! /usr/bin/env python

from .atom import Atom

class AtomICAPS2014(Atom):

    ACTION_NAMES = ["askploc", "greet", "collectmail", "gothrough", "opendoor",
                    "approach"]
    FLUENT_NAMES = ["inside", "knowinside", "open", "visiting", "mailcollected",
                    "facing", "beside", "loc"]
    TERM_NAMES = ["hasdoor", "acc", "passto", "knows"]

    def __init__(self, name, value=None, time=None, negated=False):
        super(AtomICAPS2014, self).__init__(name, value, time, negated)

        if self.type == Atom.ACTION or self.type == Atom.FLUENT: 
            if self.name in AtomICAPS2014.ACTION_NAMES:
                self.type = Atom.ACTION
                return
            if self.name in AtomICAPS2014.FLUENT_NAMES:
                self.type = Atom.FLUENT
                return
        else:
            return

        raise ValueError("Malformed atom - Unknown action/fluent: %s"%str(name))

    def conflicts_with(self, other):
        """
          Test for hard negation conflict and uniqueness constraints only.
        """

        if super(AtomICAPS2014, self).conflicts_with(other):
            return True

        # Check for uniqueness constraints
        if (self.name == "loc" and other.name == "loc" or \
            self.name == "facing" and other.name == "facing" or \
            self.name == "beside" and other.name == "beside") and \
           self.value != other.value and \
           not self.negated and not other.negated:
            return True

        # Check for uniqueness constraint for inside/knowinside
        # if the person is same, but the location is different and both 
        # fluents are not negated
        inside_names = ["inside", "knowinside"]
        if self.name in inside_names and other.name in inside_names and \
           self.value.value[0] == other.value.value[0] and \
           self.value.value[1] != other.value.value[1] and \
           not self.negated and not other.negated:
            return True

        return False

