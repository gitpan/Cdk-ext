package Cdk::Swindow;

@ISA	= qw (Cdk);

#
# This creates a new Swindow object.
#
sub new
{
   my $type		= shift;
   my %params		= @_;
   my $self		= {};
   my $name		= "${type}::new";

   # Retain the type of the object.
   $self->{'Type'}	= $type;
   
   # Set up the parameters passed in.
   my $title = Cdk::checkReq ($name, "Title", $params{'Title'});
   my $lines = Cdk::checkReq ($name, "Lines", $params{'Lines'});
   my $height = Cdk::checkReq ($name, "Height", $params{'Height'});
   my $width = Cdk::checkReq ($name, "Width", $params{'Width'});
   my $xpos = Cdk::checkDef ($name, "Xpos", $params{'Xpos'}, "CENTER");
   my $ypos = Cdk::checkDef ($name, "Ypos", $params{'Ypos'}, "CENTER");
   my $box = Cdk::checkDef ($name, "Box", $params{'Box'}, "TRUE");
   my $shadow = Cdk::checkDef ($name, "Shadow", $params{'Shadow'}, "FALSE");

   # Create the thing.
   $self->{'Me'} = Cdk::Swindow::New ($title, $lines,
					$height, $width,
					$xpos, $ypos,
					$box, $shadow);
   bless $self;
}

#
# This activates the object
#
sub activate
{
   my $self		= shift;
   my %params		= @_;
   my $name		= "$self->{'Type'}::activate";

   # Activate the object...
   if (defined $params{'Input'})
   {
      $self->{'Info'} = Cdk::Swindow::Activate ($self->{'Me'}, $params{'Input'});
   }
   else
   {
      $self->{'Info'} = Cdk::Swindow::Activate ($self->{'Me'});
   }
   return ($self->{'Info'});
}

#
# This injects a character into the widget.
#
sub inject
{
   my $self	= shift;
   my %params	= @_;
   my $name	= "$self->{'Type'}::inject";

   # Set the values.
   my $character = Cdk::checkReq ($name, "Input", $params{'Input'});

   return (Cdk::Swindow::Inject ($self->{'Me'}, $character));
}

#
# This allows us to bind a key to an action.
#
sub bind
{
   my $self	= shift;
   my %params	= @_;
   my $name	= "$self->{'Type'}::bind";
 
   # Set the values.
   my $key = Cdk::checkReq ($name, "Key", $params{'Key'});
   my $function = Cdk::checkReq ($name, "Function", $params{'Function'});
   Cdk::Swindow::Bind ($self->{'Me'}, $key, $params{'Function'});
}

#
# This sets certain attributes of the selection list.
#
sub set
{
   my $self	= shift;
   my %params	= @_;
   my $name	= "$self->{'Type'}::set";

   # Set up the parameters passed in.
   my $info = Cdk::checkReq ($name, "Info", $params{'Info'});
   my $lines = Cdk::checkReq ($name, "Lines", $params{'Lines'});
   my $box = Cdk::checkDef ($name, "Box", $params{'Box'}, "TRUE");

   Cdk::Swindow::Set ($self->{'Me'}, $params{'Info'}, $lines, $box);
}

#
# This adds a line into the scrolling window.
#
sub addline
{
   my $self	= shift;
   my %params	= @_;
   my $name	= "$self->{'Type'}::addline";

   # Set up the parameters passed in.
   my $info = Cdk::checkReq ($name, "Info", $params{'Info'});
   my $position = Cdk::checkDef ($name, "Position", $params{'Position'}, "BOTTOM");

   Cdk::Swindow::Addline ($self->{'Me'}, $info, $position);
}

#
# This allows the user to spawn a command via a scrolling window.
#
sub exec
{
   my $self	= shift;
   my %params	= @_;
   my $name	= "$self->{'Type'}::addline";

   # Set up the parameters passed in.
   my $command = Cdk::checkReq ($name, "Command", $params{'Command'});
   my $position = Cdk::checkDef ($name, "Position", $params{'Position'}, "BOTTOM");

   return Cdk::Swindow::Exec ($self->{'Me'}, $command, $position);
}

#
# This trims the scrolling window.
#
sub trim
{
   my $self	= shift;
   my %params	= @_;
   my $name	= "$self->{'Type'}::trim";

   # Set up the parameters passed in.
   my $start = Cdk::checkReq ($name, "Start", $params{'Start'});
   my $finish = Cdk::checkReq ($name, "Finish", $params{'Finish'});

   Cdk::Swindow::Trim ($self->{'Me'}, $start, $finish);
}

#
# This cleans the info from the window.
#
sub clean
{
   my $self	= shift;
   my %params	= @_;
   my $name	= "$self->{'Type'}::clean";

   Cdk::Swindow::Clean ($self->{'Me'});
}

#
# This dumps the information from the scrolling window.
#
sub get
{
   my $self	= shift;
   my %params	= @_;
   my $name	= "$self->{'Type'}::get";

   return (Cdk::Swindow::Get ($self->{'Me'}));
}

#
# This draws the object.
#
sub draw
{
   my $self	= shift;
   my %params	= @_;
   my $name	= "$self->{'Type'}::draw";

   # Set up the parameters passed in.
   my $box = Cdk::checkDef ($name, "Box", $params{'Box'}, "BOX");
   
   # Draw the object.
   Cdk::Swindow::Draw ($self->{'Me'}, $box);
}

#
# This erases the object.
#
sub erase
{
   my $self	= shift;
   Cdk::Swindow::Erase ($self->{'Me'});
}

#
# This function raises the object.
#
sub raise
{
   my $self	= shift;
   Cdk::Swindow::Raise ($self->{'Me'});
}

#
# This function lowers the object.
#
sub lower
{
   my $self	= shift;
   Cdk::Swindow::Lower ($self->{'Me'});
}

#
# This function registers the object.
#
sub register
{
   my $self	= shift;
   Cdk::Swindow::Register ($self->{'Me'});
}

#
# This function unregisters the object.
#
sub unregister
{
   my $self	= shift;
   Cdk::Swindow::Unregister ($self->{'Me'});
}

#
# This function returns the pointer to the window.
#
sub getwin
{
   my $self	= shift;
   Cdk::Swindow::GetWindow ($self->{'Me'});
}

1;
